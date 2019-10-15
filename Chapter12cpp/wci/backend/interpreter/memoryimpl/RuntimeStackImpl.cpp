/**
 * <h1>RuntimeDisplayImpl</h1>
 *
 * <p>The interpreter's runtime display.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include "RuntimeStackImpl.h"
#include "../MemoryFactory.h"

namespace wci { namespace backend { namespace interpreter { namespace memoryimpl {

using namespace wci;
using namespace wci::intermediate;

RuntimeStackImpl::RuntimeStackImpl()
{
    display = MemoryFactory::create_runtime_display();
}

}}}}  // namespace wci::backend::interpreter::memoryimpl
