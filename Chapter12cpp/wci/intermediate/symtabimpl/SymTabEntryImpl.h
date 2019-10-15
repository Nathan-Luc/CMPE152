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
#include <map>
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

/**
 * How a Pascal symbol table entry is defined.
 */
enum class DefinitionImpl
{
    CONSTANT, ENUMERATION_CONSTANT,
    TYPE, VARIABLE, FIELD,
    VALUE_PARM, VAR_PARM,
    PROGRAM_PARM,
    PROGRAM, PROCEDURE, FUNCTION,
    UNDEFINED,
};

constexpr DefinitionImpl DF_CONSTANT = DefinitionImpl::CONSTANT;
constexpr DefinitionImpl DF_ENUMERATION_CONSTANT =
                                    DefinitionImpl::ENUMERATION_CONSTANT;
constexpr DefinitionImpl DF_TYPE = DefinitionImpl::TYPE;
constexpr DefinitionImpl DF_VARIABLE = DefinitionImpl::VARIABLE;
constexpr DefinitionImpl DF_FIELD = DefinitionImpl::FIELD;
constexpr DefinitionImpl DF_VALUE_PARM = DefinitionImpl::VALUE_PARM;
constexpr DefinitionImpl DF_VAR_PARM = DefinitionImpl::VAR_PARM;
constexpr DefinitionImpl DF_PROGRAM_PARM = DefinitionImpl::PROGRAM_PARM;
constexpr DefinitionImpl DF_PROGRAM = DefinitionImpl::PROGRAM;
constexpr DefinitionImpl DF_PROCEDURE = DefinitionImpl::PROCEDURE;
constexpr DefinitionImpl DF_FUNCTION = DefinitionImpl::FUNCTION;
constexpr DefinitionImpl DF_UNDEFINED = DefinitionImpl::UNDEFINED;

/**
 * Pascal routines.
 */
enum class RoutineCodeImpl
{
    DECLARED, FORWARD,
    READ, READLN, WRITE, WRITELN,
    ABS, ARCTAN, CHR, COS, EXP, LN, ODD, ORD,
    EOF_FUNCTION, EOLN_FUNCTION,
    PRED, ROUND, SIN, SQR, SQRT, SUCC, TRUNC,
};

constexpr RoutineCodeImpl RT_DECLARED = RoutineCodeImpl::DECLARED;
constexpr RoutineCodeImpl RT_FORWARD = RoutineCodeImpl::FORWARD;
constexpr RoutineCodeImpl RT_READ = RoutineCodeImpl::READ;
constexpr RoutineCodeImpl RT_READLN = RoutineCodeImpl::READLN;
constexpr RoutineCodeImpl RT_WRITE = RoutineCodeImpl::WRITE;
constexpr RoutineCodeImpl RT_WRITELN = RoutineCodeImpl::WRITELN;
constexpr RoutineCodeImpl RT_ABS = RoutineCodeImpl::ABS;
constexpr RoutineCodeImpl RT_ARCTAN = RoutineCodeImpl::ARCTAN;
constexpr RoutineCodeImpl RT_CHR = RoutineCodeImpl::CHR;
constexpr RoutineCodeImpl RT_COS = RoutineCodeImpl::COS;
constexpr RoutineCodeImpl RT_EXP = RoutineCodeImpl::EXP;
constexpr RoutineCodeImpl RT_LN = RoutineCodeImpl::LN;
constexpr RoutineCodeImpl RT_ODD = RoutineCodeImpl::ODD;
constexpr RoutineCodeImpl RT_ORD = RoutineCodeImpl::ORD;
constexpr RoutineCodeImpl RT_EOF = RoutineCodeImpl::EOF_FUNCTION;
constexpr RoutineCodeImpl RT_EOLN = RoutineCodeImpl::EOLN_FUNCTION;
constexpr RoutineCodeImpl RT_PRED = RoutineCodeImpl::PRED;
constexpr RoutineCodeImpl RT_ROUND = RoutineCodeImpl::ROUND;
constexpr RoutineCodeImpl RT_SIN = RoutineCodeImpl::SIN;
constexpr RoutineCodeImpl RT_SQR = RoutineCodeImpl::SQR;
constexpr RoutineCodeImpl RT_SQRT = RoutineCodeImpl::SQRT;
constexpr RoutineCodeImpl RT_SUCC = RoutineCodeImpl::SUCC;
constexpr RoutineCodeImpl RT_TRUNC = RoutineCodeImpl::TRUNC;

class SymTabEntryImpl : public SymTabEntry
{
public:
    /**
     * Constructor.
     * @param name the name of the entry.
     * @param symTab the symbol table that contains this entry.
     */
    SymTabEntryImpl(const string name, SymTab *symtab);

    /**
     * Destructor.
     * NOTE: Need to figure out how to delete
     *       content.routine.parms, content.routine.routine_ids,
     *       and content.data.value.
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
     * @return the definition.
     */
    Definition get_definition() const { return definition; }

    /**
     * Setter.
     * @param definition the definition to set.
     */
    void set_definition(const Definition defn) { definition = defn; }

    /**
     * Getter.
     * @return the type specification.
     */
    TypeSpec *get_typespec() const { return typespec; }

    /**
     * Setter.
     * @param typeSpec the type specification to set.
     */
    void set_typespec(TypeSpec *spec) { typespec = spec; }

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
     * Get the routine code.
     * @return the code.
     */
    RoutineCode get_routine_code() const { return routine_code; }

    /**
     * Set the routine code.
     * @parm code the code to set.
     */
    void set_routine_code(const RoutineCode code) { routine_code = code;}

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

    /**
     * Get the routine's formal parameters.
     * @return the parameters.
     */
    vector<SymTabEntry *> *get_routine_parms() { return &routine_parms; }

    /**
     * Get the symbol table entries of the nested routines.
     * @return the symbol table entries.
     */
    vector<SymTabEntry *> *get_routine_ids() { return &routine_ids; }

    static map <DefinitionImpl, string> DEFINITION_WORDS;

private:
    static bool INITIALIZED;

    /**
     * Initialize the static maps.
     */
    static void initialize();

    string name;               // entry name
    Definition definition;     // how the identifier is defined
    SymTab *symtab;            // parent symbol table
    TypeSpec *typespec;        // type specification
    vector<int> line_numbers;  // source line numbers

    Object value;              // data value

    RoutineCode routine_code;              // routine code
    SymTab *routine_symtab;                // routine's symbol table
    ICode  *routine_icode;                 // routine's intermediate code
    vector<SymTabEntry *> routine_parms;   // routine's formal parameters
    vector<SymTabEntry *> routine_ids;     // symtab entries of nested routines
};

}}}  // namespace wci::intermediate::symtabimpl

#endif /* WCI_INTERMEDIATE_SYMTABIMPL_SYMTABENTRYIMPL_H_ */
