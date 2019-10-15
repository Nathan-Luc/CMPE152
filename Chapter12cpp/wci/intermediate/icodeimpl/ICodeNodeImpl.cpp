/**
 * <h1>ICodeNodeImpl</h1>
 *
 * <p>An implementation of a node of the intermediate code.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include <vector>
#include "ICodeNodeImpl.h"
#include "../ICodeNode.h"
#include "../ICodeFactory.h"
#include "../../Object.h"

namespace wci { namespace intermediate { namespace icodeimpl {

using namespace wci::intermediate;

bool ICodeNodeImpl::INITIALIZED = false;

EnumMap<ICodeNodeTypeImpl, string> ICodeNodeImpl::NODE_TYPE_NAMES;

void ICodeNodeImpl::initialize()
{
    if (INITIALIZED) return;

    vector<ICodeNodeTypeImpl> types =
    {
        // Program structure
        NT_PROGRAM,
        NT_PROCEDURE,
        NT_FUNCTION,

        // Statements
        NT_COMPOUND,
        NT_ASSIGN,
        NT_LOOP,
        NT_TEST,
        NT_CALL,
        NT_PARAMETERS,
        NT_IF,
        NT_SELECT,
        NT_SELECT_BRANCH,
        NT_SELECT_CONSTANTS,
        NT_NO_OP,

        // Relational operators
        NT_EQ,
        NT_NE,
        NT_LT,
        NT_LE,
        NT_GT,
        NT_GE,
        NT_NOT,

        // Additive operators
        NT_ADD,
        NT_SUBTRACT,
        NT_OR,
        NT_NEGATE,

        // Multiplicative operators
        NT_MULTIPLY,
        NT_INTEGER_DIVIDE,
        NT_FLOAT_DIVIDE,
        NT_MOD,
        NT_AND,

        // Operands
        NT_VARIABLE,
        NT_SUBSCRIPTS,
        NT_FIELD,
        NT_INTEGER_CONSTANT,
        NT_REAL_CONSTANT,
        NT_STRING_CONSTANT,
        NT_BOOLEAN_CONSTANT,

        // WRITE parameter
        NT_WRITE_PARM,
    };

    vector<string> type_names =
    {
        // Program structure
        "PROGRAM", "PROCEDURE", "FUNCTION",

        // Statements
        "COMPOUND", "ASSIGN", "LOOP", "TEST", "CALL", "PARAMETERS",
        "IF", "SELECT", "SELECT_BRANCH", "SELECT_CONSTANTS", "NO_OP",

        // Relational operators
        "EQ", "NE", "LT", "LE", "GT", "GE", "NOT",

        // Additive operators
        "ADD", "SUBTRACT", "OR", "NEGATE",

        // Multiplicative operators
        "MULTIPLY", "INTEGER_DIVIDE", "FLOAT_DIVIDE", "MOD", "AND",

        // Operands
        "VARIABLE", "SUBSCRIPTS", "FIELD",
        "INTEGER_CONSTANT", "REAL_CONSTANT",
        "STRING_CONSTANT", "BOOLEAN_CONSTANT",

        // WRITE parameter
        "WRITE_PARM",
    };

    for (int i = 0; i < types.size(); i++)
    {
        NODE_TYPE_NAMES[types[i]] = type_names[i];
    }

    INITIALIZED = true;
}

ICodeNodeImpl::ICodeNodeImpl(const ICodeNodeType type)
    : type(type), parent(nullptr), line_number(0), level(0),
      id(nullptr), typespec(nullptr)
{
    initialize();
}

ICodeNodeImpl::~ICodeNodeImpl()
{
    for (ICodeNode *node : children) if (node != nullptr) delete node;
}

ICodeNode *ICodeNodeImpl::add_child(ICodeNode *node)
{
    if (node != nullptr)
    {
        children.push_back(node);
        ((ICodeNodeImpl *) node)->parent = (ICodeNode *) this;
    }

    return node;
}

ICodeNode *ICodeNodeImpl::copy()
{
    // Create a copy with the same type.
    ICodeNodeImpl *copy =
        (ICodeNodeImpl *) ICodeFactory::create_icode_node(type);

    copy->id = id;
    copy->level = level;
    copy->typespec = typespec;
    copy->value = value;

    return (ICodeNode *) copy;
}

}}}  // namespace wci::intermediate::icodeimpl
