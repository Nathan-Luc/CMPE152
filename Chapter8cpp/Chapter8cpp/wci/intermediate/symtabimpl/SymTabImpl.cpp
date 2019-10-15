/**
 * <h1>SymTabImpl</h1>
 *
 * <p>An implementation of the symbol table.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include <string>
#include <map>
#include "SymTabImpl.h"
#include "../SymTab.h"
#include "../SymTabEntry.h"
#include "../SymTabFactory.h"

namespace wci { namespace intermediate { namespace symtabimpl {

using namespace std;
using namespace wci::intermediate;

SymTabEntry *SymTabImpl::enter(const string name)
{
    SymTabEntry *entry = SymTabFactory::create_symtab_entry(name, this);
    contents[name] = (SymTabEntryImpl *) entry;

    return entry;
}

vector<SymTabEntry *> SymTabImpl::sorted_entries()
{
    vector<SymTabEntry *> list;
    map<string, SymTabEntryImpl *>::iterator it;

    for (it = contents.begin(); it != contents.end(); it++)
    {
        list.push_back(it->second);
    }

    return list;  // sorted list of entries
}

}}}  // namespace wci::intermediate::symtabimpl
