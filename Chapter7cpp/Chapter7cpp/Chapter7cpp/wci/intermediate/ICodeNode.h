/**
 * <h1>ICodeNode</h1>
 *
 * <p>The interface for a node of the intermediate code.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#ifndef ICODENODE_H_
#define ICODENODE_H_

#include <string>
#include <vector>
#include "ICode.h"
#include "SymTabEntry.h"
#include "../frontend/Token.h"
#include "../Object.h"

namespace wci { namespace intermediate {

using namespace std;
using namespace wci;
using namespace wci::frontend;

/**
 * Intermediate code node types.
 */
enum class ICodeNodeType
{
    // to be "subclassed" by implementation-specific icode node keys
};

/**
 * Intermediate code node keys.
 */
enum class ICodeKey
{
    // to be "subclassed" by implementation-specific icode node keys
};

class ICodeNode
{
public:
    /**
     * Destructor.
     */
    virtual ~ICodeNode() {};

    /**
     * Getter.
     * @return the node type.
     */
    virtual ICodeNodeType get_type() const = 0;

    /**
     * Return the parent of this node.
     * @return the parent node.
     */
    virtual ICodeNode *get_parent() = 0;

    /**
     * Return an array list of this node's children.
     * @return the array list of children.
     */
    virtual vector<ICodeNode *> *get_children() = 0;

    /**
     * Add a child node.
     * @param node the child node.
     * @return the child node.
     */
    virtual ICodeNode *add_child(ICodeNode *node) = 0;

    /**
     * Get the statement line number.
     */
    virtual int get_line_number() const = 0;

    /**
     * Set the statement line number.
     */
    virtual void set_line_number(const int number) = 0;

    /**
     * Get the nesting level.
     * @return the nesting level.
     */
    virtual int get_level() const = 0;

    /**
     * Set the nesting level.
     * @param the nesting level to set.
     */
    virtual void set_level(const int level) = 0;

    /**
     * Get the symbol table entry.
     * @return the symbol table entry.
     */
    virtual SymTabEntry *get_id() const = 0;

    /**
     * Set the symbol table entry.
     * @param the symbol table entry to set.
     */
    virtual void set_id(SymTabEntry *id) = 0;

    /**
     * Get the value.
     * @return the value.
     */
    virtual Object *get_value() = 0;

    /**
     * Set the value.
     * @param the value to set.
     */
    virtual void set_value(const Object &value) = 0;

    /**
     * Make a copy of this node.
     * To be defined by an implementation subclass.
     * @return the copy.
     */
    virtual ICodeNode *copy() = 0;
};

}}  // namespace wci::intermediate

#endif /* ICODENODE_H_ */
