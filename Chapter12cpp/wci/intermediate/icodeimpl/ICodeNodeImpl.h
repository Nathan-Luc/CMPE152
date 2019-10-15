/**
 * <h1>ICodeNodeImpl</h1>
 *
 * <p>An implementation of a node of the intermediate code.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#ifndef ICODENODEIMPL_H_
#define ICODENODEIMPL_H_

#include <stdexcept>
#include "../ICodeNode.h"

namespace wci { namespace intermediate { namespace icodeimpl {

/**
 * Intermediate code node types.
 */
enum class ICodeNodeTypeImpl
{
    // Program structure
    PROGRAM, PROCEDURE, FUNCTION,

    // Statements
    COMPOUND, ASSIGN, LOOP, TEST, CALL, PARAMETERS,
    IF, SELECT, SELECT_BRANCH, SELECT_CONSTANTS, NO_OP,

    // Relational operators
    EQ, NE, LT, LE, GT, GE, NOT,

    // Additive operators
    ADD, SUBTRACT, OR, NEGATE,

    // Multiplicative operators
    MULTIPLY, INTEGER_DIVIDE, FLOAT_DIVIDE, MOD, AND,

    // Operands
    VARIABLE, SUBSCRIPTS, FIELD,
    INTEGER_CONSTANT, REAL_CONSTANT,
    STRING_CONSTANT, BOOLEAN_CONSTANT,

    // WRITE parameter
    WRITE_PARM,
};

constexpr ICodeNodeTypeImpl NT_PROGRAM = ICodeNodeTypeImpl::PROGRAM;
constexpr ICodeNodeTypeImpl NT_PROCEDURE = ICodeNodeTypeImpl::PROCEDURE;
constexpr ICodeNodeTypeImpl NT_FUNCTION = ICodeNodeTypeImpl::FUNCTION;

constexpr ICodeNodeTypeImpl NT_COMPOUND = ICodeNodeTypeImpl::COMPOUND;
constexpr ICodeNodeTypeImpl NT_ASSIGN = ICodeNodeTypeImpl::ASSIGN;
constexpr ICodeNodeTypeImpl NT_LOOP = ICodeNodeTypeImpl::LOOP;
constexpr ICodeNodeTypeImpl NT_TEST = ICodeNodeTypeImpl::TEST;
constexpr ICodeNodeTypeImpl NT_CALL = ICodeNodeTypeImpl::CALL;
constexpr ICodeNodeTypeImpl NT_PARAMETERS = ICodeNodeTypeImpl::PARAMETERS;
constexpr ICodeNodeTypeImpl NT_IF = ICodeNodeTypeImpl::IF;
constexpr ICodeNodeTypeImpl NT_SELECT = ICodeNodeTypeImpl::SELECT;
constexpr ICodeNodeTypeImpl NT_SELECT_BRANCH =
                                        ICodeNodeTypeImpl::SELECT_BRANCH;
constexpr ICodeNodeTypeImpl NT_SELECT_CONSTANTS =
                                     ICodeNodeTypeImpl::SELECT_CONSTANTS;
constexpr ICodeNodeTypeImpl NT_NO_OP = ICodeNodeTypeImpl::NO_OP;

constexpr ICodeNodeTypeImpl NT_EQ = ICodeNodeTypeImpl::EQ;
constexpr ICodeNodeTypeImpl NT_NE = ICodeNodeTypeImpl::NE;
constexpr ICodeNodeTypeImpl NT_LT = ICodeNodeTypeImpl::LT;
constexpr ICodeNodeTypeImpl NT_LE = ICodeNodeTypeImpl::LE;
constexpr ICodeNodeTypeImpl NT_GT = ICodeNodeTypeImpl::GT;
constexpr ICodeNodeTypeImpl NT_GE = ICodeNodeTypeImpl::GE;
constexpr ICodeNodeTypeImpl NT_NOT = ICodeNodeTypeImpl::NOT;

constexpr ICodeNodeTypeImpl NT_ADD = ICodeNodeTypeImpl::ADD;
constexpr ICodeNodeTypeImpl NT_SUBTRACT = ICodeNodeTypeImpl::SUBTRACT;
constexpr ICodeNodeTypeImpl NT_OR = ICodeNodeTypeImpl::OR;
constexpr ICodeNodeTypeImpl NT_NEGATE = ICodeNodeTypeImpl::NEGATE;

constexpr ICodeNodeTypeImpl NT_MULTIPLY = ICodeNodeTypeImpl::MULTIPLY;
constexpr ICodeNodeTypeImpl NT_INTEGER_DIVIDE = ICodeNodeTypeImpl::INTEGER_DIVIDE;
constexpr ICodeNodeTypeImpl NT_FLOAT_DIVIDE = ICodeNodeTypeImpl::FLOAT_DIVIDE;
constexpr ICodeNodeTypeImpl NT_MOD = ICodeNodeTypeImpl::MOD;
constexpr ICodeNodeTypeImpl NT_AND = ICodeNodeTypeImpl::AND;

constexpr ICodeNodeTypeImpl NT_VARIABLE = ICodeNodeTypeImpl::VARIABLE;
constexpr ICodeNodeTypeImpl NT_SUBSCRIPTS = ICodeNodeTypeImpl::SUBSCRIPTS;
constexpr ICodeNodeTypeImpl NT_FIELD = ICodeNodeTypeImpl::FIELD;
constexpr ICodeNodeTypeImpl NT_INTEGER_CONSTANT = ICodeNodeTypeImpl::INTEGER_CONSTANT;
constexpr ICodeNodeTypeImpl NT_REAL_CONSTANT = ICodeNodeTypeImpl::REAL_CONSTANT;
constexpr ICodeNodeTypeImpl NT_STRING_CONSTANT = ICodeNodeTypeImpl::STRING_CONSTANT;
constexpr ICodeNodeTypeImpl NT_BOOLEAN_CONSTANT = ICodeNodeTypeImpl::BOOLEAN_CONSTANT;

constexpr ICodeNodeTypeImpl NT_WRITE_PARM = ICodeNodeTypeImpl::WRITE_PARM;

class ICodeNodeImpl : public ICodeNode
{
public:
    /**
     * Constructor.
     * @param type the node type whose name will be the name of this node.
     */
    ICodeNodeImpl(const ICodeNodeType type);

    /**
     * Destructor.
     */
    virtual ~ICodeNodeImpl();

    /**
     * Getter.
     * @return the node type.
     */
    ICodeNodeType get_type() const { return type; }

    /**
     * Return the parent of this node.
     * @return the parent node.
     */
    ICodeNode *get_parent() { return parent; }

    /**
     * Return an array list of this node's children.
     * @return the array list of children.
     */
    vector<ICodeNode *> *get_children() { return &children; }

    /**
     * Add a child node.
     * @param node the child node.
     * @return the child node.
     */
    ICodeNode *add_child(ICodeNode *node);

    /**
     * Get the statement line number.
     */
    int get_line_number() const { return line_number; }

    /**
     * Set the statement line number.
     */
    void set_line_number(const int line_number) { this->line_number = line_number; }

    /**
     * Get the nesting level.
     * @return the nesting level.
     */
    int get_level() const { return level; }

    /**
     * Set the nesting level.
     * @param the nesting level to set.
     */
    void set_level(const int level) { this->level = level; }

    /**
     * Get the symbol table entry.
     * @return the symbol table entry.
     */
    SymTabEntry *get_id() const { return id; }

    /**
     * Set the symbol table entry.
     * @param the symbol table entry to set.
     */
    void set_id(SymTabEntry *id) { this->id = id; }

    /**
     * Return the type specification of this node.
     * @return the type specification.
     */
    TypeSpec *get_typespec() const { return typespec; }

    /**
     * Set the type specification of this node.
     * @param spec the type specification to set.
     */
    void set_typespec(TypeSpec *spec) { typespec = spec; }

    /**
     * Get the value.
     * @return the value.
     */
    Object *get_value() { return &value; }

    /**
     * Set the value.
     * @param the value to set.
     */
    void set_value(const Object &value) { this->value = value; }

    /**
     * Make a copy of this node.
     * Implementation of wci::intermediate::ICodeNode.
     * @return the copy.
     */
    ICodeNode *copy();

    static EnumMap<ICodeNodeTypeImpl, string> NODE_TYPE_NAMES;

private:
    ICodeNodeType type;            // node type
    ICodeNode *parent;             // node's parent
    vector<ICodeNode *> children;  // node's children

    int line_number;               // statement line number
    int level;                     // nesting level
    SymTabEntry *id;               // symbol table entry
    TypeSpec *typespec;            // data type specification
    Object value;                  // data value

    static bool INITIALIZED;

    /**
     * Initialize the static maps.
     */
    static void initialize();
};

}}}  // namespace wci::intermediate::icodeimpl

#endif /* ICODENODEIMPL_H_ */
