/**
 * <h1>MemoryMapImpl</h1>
 *
 * <p>The interpreter's runtime memory map.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include <string>
#include <vector>
#include <map>
#include "CellImpl.h"
#include "MemoryMapImpl.h"
#include "../Cell.h"
#include "../MemoryFactory.h"
#include "../../../intermediate/SymTab.h"
#include "../../../intermediate/symtabimpl/SymTabEntryImpl.h"
#include "../../../intermediate/TypeSpec.h"
#include "../../../intermediate/typeimpl/TypeSpecImpl.h"
#include "../../../Object.h"

namespace wci { namespace backend { namespace interpreter { namespace memoryimpl {

using namespace std;
using namespace wci;
using namespace wci::intermediate;
using namespace wci::intermediate::symtabimpl;
using namespace wci::intermediate::typeimpl;
using namespace wci::backend::interpreter;

MemoryMapImpl::MemoryMapImpl(SymTab *symtab)
{
    vector<SymTabEntry *> entries = symtab->sorted_entries();

    // Loop for each entry of the symbol table.
    for (SymTabEntry *entry : entries)
    {
        Definition defn = entry->get_definition();

        switch ((DefinitionImpl) defn)
        {
            // Not a VAR parameter: Allocate cells for the data type
            //                      in the memory map.
            case DF_VARIABLE:
            case DF_FUNCTION:
            case DF_VALUE_PARM:
            case DF_FIELD:
            {
                string *name = entry->get_name();
                TypeSpec *typespec = entry->get_typespec();
                Object value = allocate_cell_value(typespec);
                contents[*name] = MemoryFactory::create_cell(value);
                break;
            }

            // VAR parameter: Allocate a single cell for a reference.
            case DF_VAR_PARM:
            {
                string *name = entry->get_name();
                contents[*name] =
                        (CellImpl *) MemoryFactory::create_cell(nullptr);
                break;
            }

            default: break;  // should never get here
        }
    }
}

MemoryMapImpl::~MemoryMapImpl()
{
    StringMap<string, Cell *>::iterator it;

    for (it = contents.begin(); it != contents.end(); it++)
    {
        delete it->second;
    }
}

vector<pair<string, Cell*>> MemoryMapImpl::get_all_pairs()
{
    vector<pair<string, Cell*>> pairs;
    StringMap<string, Cell *>::iterator it;

    for (it = contents.begin(); it != contents.end(); it++)
    {
        pairs.push_back(*it);
    }

    return pairs;
}

Object MemoryMapImpl::allocate_cell_value(TypeSpec *typespec)
{
    TypeForm form = typespec->get_form();

    switch ((TypeFormImpl) form)
    {
        case TF_ARRAY:  return allocate_array_cells(typespec);
        case TF_RECORD: return allocate_record_map(typespec);

        default: return nullptr;  // uninitialized scalar value
    }
}

Object MemoryMapImpl::allocate_array_cells(TypeSpec *typespec)
{
    int elmt_count = typespec->get_array_elmt_count();
    TypeSpec *elmt_typespec = typespec->get_array_elmt_type();
    vector<Cell *> *array = new vector<Cell *>;

    array->reserve(elmt_count);
    for (int i = 0; i < elmt_count; ++i)
    {
        array->push_back(
            MemoryFactory::create_cell(allocate_cell_value(elmt_typespec)));
    }

    return array;
}

/**
 * Allocate the memory map for a record.
 * @param type the record type.
 * @return the allocation.
 */
MemoryMapImpl *MemoryMapImpl::allocate_record_map(TypeSpec *typespec)
{
    SymTab *symtab = typespec->get_record_symtab();
    MemoryMapImpl *memory_map =
            (MemoryMapImpl *) MemoryFactory::create_memory_map(symtab);
    return memory_map;
}

}}}}  // namespace wci::backend::interpreter::memoryimpl