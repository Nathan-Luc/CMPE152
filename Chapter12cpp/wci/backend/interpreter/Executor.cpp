/**
 * <h1>Executor</h1>
 *
 * <p>The executor for an interpreter back end.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include <iostream>
#include <fstream>
#include <chrono>
#include "Executor.h"
#include "RuntimeStack.h"
#include "RuntimeError.h"
#include "RuntimeErrorHandler.h"
#include "MemoryFactory.h"
#include "../Backend.h"
#include "../../frontend/Scanner.h"
#include "../../frontend/Source.h"
#include "../../frontend/pascal/PascalScanner.h"
#include "../../intermediate/ICodeNode.h"
#include "../../intermediate/ICodeFactory.h"
#include "../../intermediate/icodeimpl/ICodeNodeImpl.h"
#include "../../message/Message.h"
#include "executors/CallDeclaredExecutor.h"

namespace wci { namespace backend { namespace interpreter {

using namespace std;
using namespace std::chrono;
using namespace wci::frontend;
using namespace wci::frontend::pascal;
using namespace wci::intermediate;
using namespace wci::intermediate::icodeimpl;
using namespace wci::backend;
using namespace wci::backend::interpreter::executors;
using namespace wci::message;

bool Executor::INITIALIZED = false;

int Executor::execution_count = 0;
RuntimeStack *Executor::runtime_stack;
RuntimeErrorHandler Executor::error_handler;

Scanner *Executor::std_in;
ostream *Executor::std_out;

void Executor::initialize()
{
    if (INITIALIZED) return;

    runtime_stack = MemoryFactory::create_runtime_stack();
    std_in  = new PascalScanner(new Source(cin));
    std_out = &cout;

    INITIALIZED = true;
}

Executor::Executor()
{
    RuntimeError::initialize();
    initialize();
}

void Executor::process(ICode *icode, SymTabStack *symtab_stack)
    throw (string)
{
    this->symtab_stack = symtab_stack;
    this->icode = icode;

    steady_clock::time_point start_time = steady_clock::now();

    SymTabEntry *program_id = symtab_stack->get_program_id();

    // Construct an artificial CALL node to the main program.
    ICodeNode *call_node =
        ICodeFactory::create_icode_node((ICodeNodeType) NT_CALL);
    call_node->set_id(program_id);
    call_node->set_line_number(icode->get_root()->get_line_number());

    // Execute the main program.
    CallDeclaredExecutor call_executor(this);
    call_executor.execute(call_node);

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

