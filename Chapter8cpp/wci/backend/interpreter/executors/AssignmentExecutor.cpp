/**
 * <h1>AssignmentExecutor</h1>
 *
 * <p>Execute an assignment statement.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include <string>
#include "AssignmentExecutor.h"
#include "StatementExecutor.h"
#include "ExpressionExecutor.h"
#include "../../../Object.h"
#include "../../../intermediate/ICodeNode.h"
#include "../../../intermediate/icodeimpl/ICodeNodeImpl.h"
#include "../../../intermediate/SymTabEntry.h"
#include "../../../intermediate/symtabimpl/SymTabEntryImpl.h"
#include "../../../message/Message.h"

namespace wci { namespace backend { namespace interpreter { namespace executors {

using namespace std;
using namespace wci;
using namespace wci::backend::interpreter;
using namespace wci::intermediate;
using namespace wci::intermediate::symtabimpl;
using namespace wci::message;

Message AssignmentExecutor::ASSIGN_MESSAGE(ASSIGN);

Object AssignmentExecutor::execute(ICodeNode *node)
{
    // The ASSIGN node's children are the target variable
    // and the expression.
    vector<ICodeNode *> *children = node->get_children();
    ICodeNode *variable_node = (*children)[0];
    ICodeNode *expression_node = (*children)[1];
    SymTabEntry *variable_id = variable_node->get_id();

    // Execute the expression and get its value.
    ExpressionExecutor expression_executor(this);
    Object result_value = expression_executor.execute(expression_node);

    // Set the value as an attribute of the
    // target variable's symbol table entry.
	variable_id->set_data_value(result_value);

    // Send a message about the assignment.
    send_assign_message(node, *(variable_id->get_name()), result_value);

    ++execution_count;
    return Object();  // empty
}

void AssignmentExecutor::send_assign_message(ICodeNode *node,
                                             string& variable_name,
                                             Object& data_value)
{
    string value_str = stringify(data_value);
    ASSIGN_MESSAGE.line_number = node->get_line_number();
    ASSIGN_MESSAGE.content.assign.variable_name = variable_name.c_str();
    ASSIGN_MESSAGE.content.assign.result_value = value_str.c_str();
    send_message(ASSIGN_MESSAGE);
}

}}}}  // namespace wci::backend::interpreter::executors
