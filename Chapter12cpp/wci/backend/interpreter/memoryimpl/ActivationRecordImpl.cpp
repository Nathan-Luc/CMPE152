/**
 * <h1>ActivationRecord</h1>
 *
 * <p>Interface for the interpreter's runtime activation record.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include "ActivationRecordImpl.h"
#include "../MemoryFactory.h"
#include "../../../intermediate/symtabimpl/SymTabEntryImpl.h"

namespace wci { namespace backend { namespace interpreter { namespace memoryimpl {

using namespace std;
using namespace wci;
using namespace wci::intermediate;
using namespace wci::intermediate::symtabimpl;

ActivationRecordImpl::ActivationRecordImpl(SymTabEntry *routine_id)
    : link(nullptr), routine_id(routine_id)
{
    SymTab *symtab = routine_id->get_routine_symtab();
    nesting_level = symtab->get_nesting_level();
    memory_map = MemoryFactory::create_memory_map(symtab);
}

}}}}  // namespace wci::backend::interpreter::memoryimpl
