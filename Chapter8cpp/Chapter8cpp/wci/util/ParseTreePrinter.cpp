/**
 * <h1>ParseTreePrinter</h1>
 *
 * <p>Print a parse tree.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include <iostream>
#include <string>
#include <vector>
#include "ParseTreePrinter.h"
#include "../Object.h"
#include "../intermediate/ICode.h"
#include "../intermediate/ICodeNode.h"
#include "../intermediate/icodeimpl/ICodeNodeImpl.h"

namespace wci { namespace util {

using namespace std;
using namespace wci::intermediate;
using namespace wci::intermediate::icodeimpl;

const int ParseTreePrinter::INDENT_WIDTH = 4;
const int ParseTreePrinter::LINE_WIDTH = 80;
string ParseTreePrinter::INDENT = string(INDENT_WIDTH, ' ');

void ParseTreePrinter::print(ICode *icode)
{
    cout << endl << "===== INTERMEDIATE CODE =====" << endl << endl;

    line = "";
    indentation = "";

    print_node((ICodeNodeImpl *) (icode->get_root()));
    print_line();
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
