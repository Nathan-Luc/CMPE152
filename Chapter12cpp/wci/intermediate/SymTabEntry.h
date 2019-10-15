/**
 * <h1>SymTabEntry</h1>
 *
 * <p>The interface for a symbol table entry.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#ifndef WCI_INTERMEDIATE_SYMTABENTRY_H_
#define WCI_INTERMEDIATE_SYMTABENTRY_H_

#include <vector>
#include <string>
#include "SymTab.h"
#include "ICode.h"
#include "../Object.h"

namespace wci { namespace intermediate {

using namespace std;
using namespace wci;

/**
 * Symbol table entry keys.
 */
enum class SymTabKey
{
    // to be "subclassed" by implementation-specific symbol table keys
};

class SymTab;    // forward declaration
class TypeSpec;  // forward declaration

/**
 * Symbol table definitions.
 */
enum class Definition
{
    // to be "subclassed" by implementation-specific symbol table definitions
};

/**
 * Routine codes.
 */
enum class RoutineCode
{
    // to be "subclassed" by implementation-specific routine codes
};

class SymTabEntry
{
public:
    /**
     * Destructor.
     */
    virtual ~SymTabEntry() {}

    /**
     * Getter.
     * @return the name of the entry.
     */
    virtual string *get_name() = 0;

    /**
     * Getter.
     * @return the symbol table that contains this entry.
     */
    virtual SymTab *get_symtab() const = 0;

    /**
     * Getter.
     * @return the definition.
     */
    virtual Definition get_definition() const = 0;

    /**
     * Setter.
     * @param definition the definition to set.
     */
    virtual void set_definition(const Definition defn) = 0;

    /**
     * Getter.
     * @return the type specification.
     */
    virtual TypeSpec *get_typespec() const = 0;

    /**
     * Setter.
     * @param typeSpec the type specification to set.
     */
    virtual void set_typespec(TypeSpec *spec) = 0;

    /**
     * Getter.
     * @return the list of source line numbers.
     */
    virtual vector<int> *get_line_numbers() = 0;

    /**
     * Append a source line number to the entry.
     * @param line_number the line number to append.
     */
    virtual void append_line_number(const int line_number) = 0;

    /**
     * Get the data value.
     * @return the value.
     */
    virtual Object *get_data_value() = 0;

    /**
     * Set the data value.
     * @parm value the value to set.
     */
    virtual void set_data_value(const Object& value) = 0;

    /**
     * Get the routine code.
     * @return the code.
     */
    virtual RoutineCode get_routine_code() const  = 0;

    /**
     * Set the routine code.
     * @parm code the code to set.
     */
    virtual void set_routine_code(const RoutineCode code) = 0;

    /**
     * Get the routine's symbol table.
     * @return the symbol table.
     */
    virtual SymTab *get_routine_symtab() const  = 0;

    /**
     * Set the routine's symbol table.
     * @parm symtab the symbol table to set.
     */
    virtual void set_routine_symtab(SymTab *symtab) = 0;

    /**
     * Get the routine's intermediate code.
     * @return the intermediate code.
     */
    virtual ICode *get_routine_icode() const = 0;

    /**
     * Set the routine's intermediate code.
     * @parm icode the intermediate code to set.
     */
    virtual void set_routine_icode(ICode *icode) = 0;

    /**
     * Get the routine's formal parameters.
     * @return the parameters.
     */
    virtual vector<SymTabEntry *> *get_routine_parms() = 0;

    /**
     * Get the symbol table entries of the nested routines.
     * @return the symbol table entries.
     */
    virtual vector<SymTabEntry *> *get_routine_ids() = 0;
};

}} // namespace wci::intermediate

#endif /* WCI_INTERMEDIATE_SYMTABENTRY_H_ */
