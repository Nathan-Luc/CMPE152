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

SymTabStackImpl::SymTabStackImpl() : current_nesting_level(0), program_id(nullptr)
{
    stack.push_back(SymTabFactory::create_symtab(0));
}

SymTabStackImpl::~SymTabStackImpl()
{
    for (SymTab *symtab : stack) if (symtab != nullptr) delete symtab;
}

SymTab *SymTabStackImpl::push()
{
    SymTab *symtab = SymTabFactory::create_symtab(++current_nesting_level);
    stack.push_back(symtab);

    return symtab;
}

SymTab *SymTabStackImpl::push(SymTab *symtab)
{
    ++current_nesting_level;
    stack.push_back(symtab);

    return symtab;
}

SymTab *SymTabStackImpl::pop()
{
    SymTab *symtab = stack[current_nesting_level];
    stack.erase(stack.begin() + current_nesting_level);
    current_nesting_level--;

    return symtab;
}

SymTabEntry *SymTabStackImpl::lookup(const string name) const
{
    SymTabEntry *found_entry = nullptr;

    // Search the current and enclosing scopes.
    for (int i = current_nesting_level;
         (i >= 0) && (found_entry == nullptr); --i)
    {
        found_entry = stack[i]->lookup(name);
    }

    return found_entry;
}

}}}  // namespace wci::intermediate::symtabimpl
