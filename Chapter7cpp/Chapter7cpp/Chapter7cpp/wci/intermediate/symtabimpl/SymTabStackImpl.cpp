/**
 * <h1>SymTabStack</h1>
 *
 * <p>An implementation of the symbol table stack.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include <vector>
#include "SymTabStackImpl.h"
#include "../SymTabFactory.h"

namespace wci { namespace intermediate { namespace symtabimpl {

using namespace std;
using namespace wci::intermediate;

SymTabStackImpl::SymTabStackImpl() : current_nesting_level(0)
{
    stack.push_back(SymTabFactory::create_symtab(0));
}

SymTabStackImpl::~SymTabStackImpl()
{
    for (SymTab *symtab : stack) if (symtab != nullptr) delete symtab;
}

SymTabEntry *SymTabStackImpl::lookup(const string name) const
{
    return lookup_local(name);
}

}}}  // namespace wci::intermediate::symtabimpl
