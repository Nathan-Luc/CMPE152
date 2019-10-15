/**
 * <h1>Pascal</h1>
 *
 * <p>Compile or interpret a Pascal source program.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Pascal.h"
#include "wci/frontend/Parser.h"
#include "wci/frontend/Scanner.h"
#include "wci/frontend/Source.h"
#include "wci/frontend/FrontendFactory.h"
#include "wci/frontend/pascal/PascalToken.h"
#include "wci/intermediate/SymTab.h"
#include "wci/intermediate/ICode.h"
#include "wci/backend/Backend.h"
#include "wci/backend/BackendFactory.h"
#include "wci/message/Message.h"
#include "wci/message/MessageListener.h"
#include "wci/util/CrossReferencer.h"
#include "wci/util/ParseTreePrinter.h"

using namespace std;
using namespace wci::frontend;
using namespace wci::frontend::pascal;
using namespace wci::intermediate;
using namespace wci::backend;
using namespace wci::message;
using namespace wci::util;

const string FLAGS = "[-ix]";
const string USAGE =
    "Usage: Pascal execute|compile " + FLAGS + " <source file path>";

/**
 * The main method.
 * @param args command-line arguments: "compile" or "execute" followed by
 *             optional flags followed by the source file path.
 */
int main(int argc, char *args[])
{
    try
    {
        // Operation.
        string operation = args[1];
        if ((operation != "compile") && (operation != "execute"))
        {
            throw USAGE;
        }

        // Flags.
        string flags = "";
        int i = 1;
        while ((++i < argc) && (args[i][0] == '-'))
        {
            flags += string(args[i]).substr(1);
        }

        // Source path.
        if (i < argc)
        {
            string path = args[i];
            Pascal(operation, path, flags);
        }
        else
        {
            throw string("Missing source file.");
        }
    }
    catch (string& msg)
    {
        cout << "***** ERROR: " << msg << endl;
    }

    return 0;
}

Pascal::Pascal(string operation, string file_path, string flags)
    throw (string)
    : icode(nullptr), symtab_stack(nullptr), backend(nullptr)
{
    ifstream input;
    input.open(file_path);
    if (input.fail())
    {
        throw string("Failed to open source file " + file_path);
    }

    Options::intermediate = flags.find('i') != string::npos;
    Options::xref         = flags.find('x') != string::npos;

    source = new Source(input);
    source->add_message_listener(this);

    parser = FrontendFactory::create_parser("Pascal", "top-down", source);
    parser->add_message_listener(this);
    parser->parse();

    source->close();

    if (parser->get_error_count() == 0)
    {
        symtab_stack = parser->get_symtab_stack();
        icode = parser->get_icode();

        if (Options::xref)
        {
            CrossReferencer cross_referencer;
            cross_referencer.print(symtab_stack);
        }

        if (Options::intermediate)
        {
            ParseTreePrinter tree_printer;
            tree_printer.print(icode);
        }

        first_output_message = true;

        backend = BackendFactory::create_backend(operation);
        backend->add_message_listener(this);
        backend->process(icode, symtab_stack);
    }
}

Pascal::~Pascal()
{
    if (parser       != nullptr) delete parser;
    if (source       != nullptr) delete source;
    if (icode        != nullptr) delete icode;
    if (symtab_stack != nullptr) delete symtab_stack;
    if (backend      != nullptr) delete backend;
}

const string Pascal::SOURCE_LINE_FORMAT = "%03d %s\n";

const string Pascal::PARSER_SUMMARY_FORMAT =
    string("\n%20s source lines.\n%20d syntax errors.\n") +
    string("%20.2f seconds total parsing time.\n");

const string Pascal::INTERPRETER_SUMMARY_FORMAT =
    string("\n%20s statements executed.\n") +
    string("%20d runtime errors.\n") +
    string("%20.2f seconds total execution time.\n");

const string Pascal::COMPILER_SUMMARY_FORMAT =
    string("\n%20s instructions generated.\n") +
    string("%20.2f seconds total code generation time.\n");

const string Pascal::LINE_FORMAT   = ">>> AT LINE %03d\n";
const string Pascal::ASSIGN_FORMAT = ">>> AT LINE %03d: %s = %s\n";
const string Pascal::RUNTIME_ERROR_FORMAT =
        "*** RUNTIME ERROR AT LINE %03d: %s\n";

const int Pascal::PREFIX_WIDTH = 5;

/**
 * Listen for messages.
 * @param message the received message.
 */
void Pascal::message_received(Message& message)
{
    switch (message.type)
    {
        case SOURCE_LINE:
        {
            printf(SOURCE_LINE_FORMAT.c_str(),
                   message.content.source_line.line_number,
                   message.content.source_line.line_text);
            break;
        }

        case PARSER_SUMMARY:
        {
            string line_count = commafy(message.content.parser_summary.line_count);
            int error_count = message.content.parser_summary.error_count;
            double elapsed_time = message.content.parser_summary.elapsed_time;

            printf(PARSER_SUMMARY_FORMAT.c_str(),
                   line_count.c_str(), error_count, elapsed_time);
            break;
        }

        case INTERPRETER_SUMMARY:
        {
            string execution_count =
                    commafy(message.content.interpreter_summary.execution_count);

            printf(INTERPRETER_SUMMARY_FORMAT.c_str(),
                   execution_count.c_str(),
                   message.content.interpreter_summary.runtime_errors,
                   message.content.interpreter_summary.elapsed_time);
            break;
        }

        case COMPILER_SUMMARY:
        {
            string instruction_count =
                    commafy(message.content.compiler_summary.instruction_count);

            printf(COMPILER_SUMMARY_FORMAT.c_str(),
                   instruction_count.c_str(),
                   message.content.compiler_summary.elapsed_time);
            break;
        }

        case ASSIGN:
        {
            if (first_output_message)
            {
                cout << endl << "===== OUTPUT =====" << endl << endl;
                first_output_message = false;
            }

            printf(ASSIGN_FORMAT.c_str(), message.line_number,
                   message.content.assign.variable_name,
                   message.content.assign.result_value);
            break;
        }

        case SYNTAX_ERROR:
        {
            int position         = message.content.syntax_error.position;
            string token_text    = message.content.syntax_error.token_text;
            string error_message = message.content.syntax_error.error_message;
            string flag = "";

            if (position >= 0)
            {
                int space_count = PREFIX_WIDTH + position;

                // Spaces up to the error position.
                for (int i = 1; i < space_count; ++i) flag += " ";

                // A pointer to the error.
                flag += "^\n";
            }

            flag += "*** " + error_message;

            // Text, if any, of the bad token.
            if (strlen(message.content.syntax_error.token_text) > 0)
            {
                flag += " [at \"" + token_text + "\"]\n";
            }

            cout << flag;
            break;
        }

        case RUNTIME_ERROR:
        {
            printf(RUNTIME_ERROR_FORMAT.c_str(),
                   message.line_number,
                   message.content.runtime_error.error_message);
            break;
        }

        default: break;
    }
}

string Pascal::commafy(const int value) const
{
    string str = to_string(value);
    int pos = str.length() - 3;

    while (pos > 0)
    {
        str.insert(pos, ",");
        pos -= 3;
    }

    return str;
}
