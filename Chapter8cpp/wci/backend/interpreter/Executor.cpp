/**
 * <h1>Executor</h1>
 *
 * <p>The executor for an interpreter back end.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include <chrono>
#include "Executor.h"
#include "RuntimeError.h"
#include "../Backend.h"
#include "../../intermediate/ICodeNode.h"
#include "../../message/Message.h"
#include "executors/StatementExecutor.h"

namespace wci { namespace backend { namespace interpreter {

using namespace std;
using namespace std::chrono;
using namespace wci::intermediate;
using namespace wci::backend;
using namespace wci::backend::interpreter::executors;
using namespace wci::message;

RuntimeErrorHandler Executor::error_handler;
int Executor::execution_count = 0;

Executor::Executor()
{
    RuntimeError::initialize();
}

void Executor::process(ICode *icode, SymTabStack *symtab_stack) throw (string)
{
    this->symtab_stack = symtab_stack;
    this->icode = icode;

    steady_clock::time_point start_time = steady_clock::now();

    // Get the root node of the intermediate code and execute.
    ICodeNode *root_node = icode->get_root();
    StatementExecutor statement_executor(this);
    statement_executor.execute(root_node);

    // Send the interpreter summary message.
    steady_clock::time_point end_time = steady_clock::now();
    double elapsed_time =
            duration_cast<duration<double>>(end_time - start_time).count();
    Message message(INTERPRETER_SUMMARY);
    message.content.interpreter_summary.execution_count = execution_count;
    message.content.interpreter_summary.runtime_errors =
                                           error_handler.get_error_count();
    message.content.interpreter_summary.elapsed_time = elapsed_time;
    send_message(message);
}

}}} // namespace wci::backend::interpreter

