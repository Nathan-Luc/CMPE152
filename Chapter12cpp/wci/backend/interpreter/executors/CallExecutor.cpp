/**
 * <h1>CallExecutor</h1>
 *
 * <p>Execute a call to a procedure or function.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include "CallExecutor.h"
#include "CallDeclaredExecutor.h"
#include "CallStandardExecutor.h"
#include "StatementExecutor.h"
#include "../../../intermediate/ICodeNode.h"
#include "../../../intermediate/SymTabEntry.h"
#include "../../../intermediate/symtabimpl/SymTabEntryImpl.h"
#include "../../../intermediate/icodeimpl/ICodeNodeImpl.h"

namespace wci { namespace backend { namespace interpreter { namespace executors {

using namespace std;
using namespace wci;
using namespace wci::backend::interpreter;
using namespace wci::intermediate;
using namespace wci::intermediate::symtabimpl;
using namespace wci::intermediate::icodeimpl;

Object CallExecutor::execute(ICodeNode *node)
{
    SymTabEntry *routine_id = node->get_id();
    RoutineCode routine_code = routine_id->get_routine_code();

    ++execution_count;  // count the call statement

    if (routine_code == (RoutineCode) RT_DECLARED)
    {
        CallDeclaredExecutor call_executor(this);
        return call_executor.execute(node);
    }
    else
    {
        CallStandardExecutor call_executor(this);
        return call_executor.execute(node);
    }
}

}}}}  // namespace wci::backend::interpreter::executors
