/**
 * <h1>SymTabEntryImpl</h1>
 *
 * <p>An implementation of a symbol table entry.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#ifndef WCI_INTERMEDIATE_SYMTABIMPL_SYMTABENTRYIMPL_H_
#define WCI_INTERMEDIATE_SYMTABIMPL_SYMTABENTRYIMPL_H_

#include <string>
#include "../SymTab.h"
#include "../SymTabEntry.h"
#include "../../Object.h"

namespace wci { namespace intermediate { namespace symtabimpl {

using namespace std;
using namespace wci::intermediate;

/**
 * Symbol table entry keys.
 */
enum class SymTabKeyImpl
{
    // Constant.
    CONSTANT_VALUE,

    // Procedure or function.
    ROUTINE_CODE, ROUTINE_SYMTAB, ROUTINE_ICODE,
    ROUTINE_PARMS, ROUTINE_ROUTINES,

    // Variable or record field value.
    DATA_VALUE
};

constexpr SymTabKeyImpl CONSTANT_VALUE = SymTabKeyImpl::CONSTANT_VALUE;
constexpr SymTabKeyImpl ROUTINE_CODE = SymTabKeyImpl::ROUTINE_CODE;
constexpr SymTabKeyImpl ROUTINE_SYMTAB = SymTabKeyImpl::ROUTINE_SYMTAB;
constexpr SymTabKeyImpl ROUTINE_ICODE = SymTabKeyImpl::ROUTINE_ICODE;
constexpr SymTabKeyImpl ROUTINE_PARMS = SymTabKeyImpl::ROUTINE_PARMS;
constexpr SymTabKeyImpl ROUTINE_ROUTINES = SymTabKeyImpl::ROUTINE_ROUTINES;
constexpr SymTabKeyImpl DATA_VALUE = SymTabKeyImpl::DATA_VALUE;

class SymTabEntryImpl : public SymTabEntry
{
public:
    /**
     * Constructor.
     * @param name the name of the entry.
     * @param symTab the symbol table that contains this entry.
     */
    SymTabEntryImpl(const string name, SymTab *symtab):
        name(name), symtab(symtab) {}

    /**
     * Destructor.
     */
    virtual ~SymTabEntryImpl() {}

    /**
     * Getter.
     * @return the name of the entry.
     */
    string *get_name() { return &name; }

    /**
     * Getter.
     * @return the symbol table that contains this entry.
     */
    SymTab *get_symtab() const { return symtab; }

    /**
     * Getter.
     * @return the list of source line numbers.
     */
    vector<int> *get_line_numbers() { return &line_numbers; }

    /**
     * Append a source line number to the entry.
     * @param line_number the line number to append.
     */
    void append_line_number(const int line_number)
    {
        line_numbers.push_back(line_number);
    }

    /**
     * Get the data value.
     * @return the value.
     */
    Object *get_data_value() { return &value; }

    /**
     * Set the data value.
     * @parm val the value to set.
     */
    void set_data_value(const Object& val) { value = val; }

    /**
     * Get the routine's symbol table.
     * @return the symbol table.
     */
    SymTab *get_routine_symtab() const { return routine_symtab; }

    /**
     * Set the routine's symbol table.
     * @parm symtab the symbol table to set.
     */
    void set_routine_symtab(SymTab *symtab) {  routine_symtab = symtab; }

    /**
     * Get the routine's intermediate code.
     * @return the intermediate code.
     */
    ICode *get_routine_icode() const { return routine_icode; }

    /**
     * Set the routine's intermediate code.
     * @parm icode the intermediate code to set.
     */
    void set_routine_icode(ICode *icode) { routine_icode = icode; }

private:
    static bool INITIALIZED;

    /**
     * Initialize the static maps.
     */
    static void initialize();

    string name;               // entry name
    SymTab *symtab;            // parent symbol table
    vector<int> line_numbers;  // source line numbers

    Object value;              // data value

    SymTab *routine_symtab;                // routine's symbol table
    ICode  *routine_icode;                 // routine's intermediate code
};

}}}  // namespace wci::intermediate::symtabimpl

#endif /* WCI_INTERMEDIATE_SYMTABIMPL_SYMTABENTRYIMPL_H_ */
