/**
 * <h1>ParseTreePrinter</h1>
 *
 * <p>Print a parse tree.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include "ParseTreePrinter.h"
#include "../intermediate/SymTab.h"
#include "../intermediate/SymTabEntry.h"
#include "../intermediate/symtabimpl/SymTabImpl.h"
#include "../intermediate/symtabimpl/SymTabEntryImpl.h"
#include "../intermediate/ICode.h"
#include "../intermediate/ICodeNode.h"
#include "../intermediate/icodeimpl/ICodeNodeImpl.h"
#include "../intermediate/TypeSpec.h"
#include "../intermediate/typeimpl/TypeSpecImpl.h"

namespace wci { namespace util {

using namespace std;
using namespace wci::intermediate;
using namespace wci::intermediate::symtabimpl;
using namespace wci::intermediate::icodeimpl;
using namespace wci::intermediate::typeimpl;

const int ParseTreePrinter::INDENT_WIDTH = 4;
const int ParseTreePrinter::LINE_WIDTH = 80;
string ParseTreePrinter::INDENT = string(INDENT_WIDTH, ' ');

void ParseTreePrinter::print(SymTabStack *symtab_stack)
{
    cout << endl << "===== INTERMEDIATE CODE =====" << endl;

    line = "";
    indentation = "";

    SymTabEntry *program_id = symtab_stack->get_program_id();
    print_routine(program_id);
}

void ParseTreePrinter::print_routine(SymTabEntry *routine_id)
{
    Definition defn = routine_id->get_definition();
    cout << endl << "*** "
         << SymTabEntryImpl::DEFINITION_WORDS[(DefinitionImpl) defn]
         << " " << *(routine_id->get_name()) << " ***" << endl << endl;

    // Print the intermediate code in the routine's symbol table entry.
    ICode *icode = routine_id->get_routine_icode();
    if (icode != nullptr)
    {
        if (icode->get_root() != nullptr)
        {
            print_node((ICodeNodeImpl *) (icode->get_root()));
        }
    }

    // Print any procedures and functions defined in the routine.
    vector<SymTabEntry *> *routine_ids = routine_id->get_routine_ids();
    if (routine_ids != nullptr)
    {
        for (SymTabEntry *routine_id : *routine_ids)
        {
            print_routine(routine_id);
        }
    }
}

void ParseTreePrinter::print_node(ICodeNodeImpl *node)
{
    // Opening tag.
    string type_name =
            ICodeNodeImpl::NODE_TYPE_NAMES[(ICodeNodeTypeImpl) node->get_type()];
    append(indentation);
    append("<" + type_name);

    print_attributes(node);
    print_type_spec(node);

    vector<ICodeNode *> *child_nodes = node->get_children();

    // Print the node's children followed by the closing tag.
    if (child_nodes->size() > 0)
    {
        append(">");
        print_line();

        print_child_nodes(child_nodes);
        append(indentation); append("</" + type_name + ">");
    }

    // No children: Close off the tag.
    else
    {
        append(" "); append("/>");
    }

    print_line();
}

void ParseTreePrinter::print_attributes(ICodeNodeImpl *node)
{
    string save_indentation = indentation;
    indentation += INDENT;

    int line_number = node->get_line_number();
    if (line_number > 0)
    {
        print_attribute("line", to_string(line_number));
    }

    SymTabEntry *id = node->get_id();
    if (id != nullptr)
    {
        string *name = id->get_name();
        print_attribute("id", *name);
        print_attribute("level", to_string(id->get_symtab()->get_nesting_level()));
    }

    Object *value = node->get_value();
    if (!value->empty())
    {
        print_attribute("value", stringify(*value));
    }

    indentation = save_indentation;
}

void ParseTreePrinter::print_attribute(string key_name, string value_string)
{
    string text = key_name + "=\"" + value_string + "\"";
    append(" "); append(text);
}

void ParseTreePrinter::print_child_nodes(vector<ICodeNode *> *child_nodes)
{
    string saveIndentation = indentation;
    indentation += INDENT;
    for (ICodeNode *child : *child_nodes) print_node((ICodeNodeImpl *) child);
    indentation = saveIndentation;
}

void ParseTreePrinter::print_type_spec(ICodeNodeImpl *node)
{
    TypeSpec *typespec = node->get_typespec();

    if (typespec != nullptr)
    {
        string save_margin = indentation;
        indentation += INDENT;

        string type_name;
        SymTabEntry *type_id = typespec->get_identifier();

        // Named type: Print the type identifier's name.
        if (type_id != nullptr) type_name = *(type_id->get_name());

        // Unnamed type: Print an artificial type identifier name.
        else
        {
            hash<TypeSpec *> typespec_hash;
            hash<string>     form_hash;
            TypeFormImpl form = (TypeFormImpl) typespec->get_form();
            string form_name = TypeSpecImpl::TYPE_FORM_NAMES[form];
            stringstream stream;
            stream << hex << abs((int) (  typespec_hash(typespec)
                                        + form_hash(form_name)));
            type_name = "$anon_" + stream.str();
        }

        print_attribute("type_id", type_name);
        indentation = save_margin;
    }
}

void ParseTreePrinter::append(string text)
{
    int text_length = text.length();
    bool line_break = false;

    // Wrap lines that are too long.
    if (length + text_length > LINE_WIDTH)
    {
        print_line();
        line += indentation;
        length = indentation.length();
        line_break = true;
    }

    // Append the text.
    if (!(line_break && (text == " ")))
    {
        line += text;
        length += text_length;
    }
}

void ParseTreePrinter::print_line()
{
    if (length > 0)
    {
        cout << line << endl;
        line = "";
        length = 0;
    }
}

}}  // namespace wci::util
