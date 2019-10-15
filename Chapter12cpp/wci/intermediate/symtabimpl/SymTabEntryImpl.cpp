/**
 * <h1>SymTabEntryImpl</h1>
 *
 * <p>An implementation of a symbol table entry.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */

#include <string>
#include <vector>
#include <map>
#include "SymTabEntryImpl.h"
#include "../SymTab.h"
#include "../SymTabEntry.h"

namespace wci { namespace intermediate { namespace symtabimpl {

using namespace std;
using namespace wci;
using namespace wci::intermediate;

bool SymTabEntryImpl::INITIALIZED = false;

map <DefinitionImpl, string> SymTabEntryImpl::DEFINITION_WORDS;

void SymTabEntryImpl::initialize()
{
    if (INITIALIZED) return;

    vector<string> defn_words =
    {
        "constant", "enumeration constant",
        "type", "variable", "record field",
        "value parameter", "VAR parameter",
        "program parameter",
        "PROGRAM", "PROCEDURE", "FUNCTION",
        "undefined",
    };

    vector<DefinitionImpl> defns =
    {
        DefinitionImpl::CONSTANT,
        DefinitionImpl::ENUMERATION_CONSTANT,
        DefinitionImpl::TYPE,
        DefinitionImpl::VARIABLE,
        DefinitionImpl::FIELD,
        DefinitionImpl::VALUE_PARM,
        DefinitionImpl::VAR_PARM,
        DefinitionImpl::PROGRAM_PARM,
        DefinitionImpl::PROGRAM,
        DefinitionImpl::PROCEDURE,
        DefinitionImpl::FUNCTION,
        DefinitionImpl::UNDEFINED,
    };

    for (int i = 0; i < defn_words.size(); i++)
    {
        DEFINITION_WORDS[defns[i]] = defn_words[i];
    }

    INITIALIZED = true;
}

SymTabEntryImpl::SymTabEntryImpl(const string name, SymTab *symtab)
    : name(name), definition((Definition) -1), symtab(symtab),
      typespec(nullptr), routine_symtab(nullptr), routine_icode(nullptr)
{
    initialize();
}

}}}  // namespace wci::intermediate::symtabimpl
