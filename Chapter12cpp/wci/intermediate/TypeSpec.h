/**
 * <h1>TypeSpec</h1>
 *
 * <p>The interface for a type specification.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#ifndef TYPESPEC_H_
#define TYPESPEC_H_

#include <vector>
#include <map>
#include "SymTabEntry.h"
#include "../Object.h"

namespace wci { namespace intermediate {

using namespace std;

/**
 * Type specification form
 */
enum class TypeForm
{
    // to be "subclassed" by implementation-specific type forms
};

/**
 * Type specification key
 */
enum class TypeKey
{
    // to be "subclassed" by implementation-specific type keys
};

class TypeSpec;  // forward declaration

class TypeSpec
{
public:
    /**
     * Destructor.
     */
    virtual ~TypeSpec() {}

    /**
     * Getter
     * @return the type form.
     */
    virtual TypeForm get_form() const = 0;

    /**
     * Getter.
     * @return the type identifier (symbol table entry).
     */
    virtual SymTabEntry *get_identifier() const = 0;

    /**
     * Setter.
     * @param id the type identifier (symbol table entry).
     */
    virtual void set_identifier(SymTabEntry *id) = 0;

    /**
     * To be defined by an implementation subclass.
     * @return true if this is a Pascal string type.
     */
    virtual bool is_pascal_string() = 0;

    /**
     * To be defined by an implementation subclass.
     * @return the base type of this type.
     */
    virtual TypeSpec *base_type() = 0;

    /**
     * Set the subrange base type.
     * @param base_type the base type to set.
     */
    virtual void set_base_type(TypeSpec *base_type) = 0;

    /**
     * Get the subrange minimum value.
     * @return the value.
     */
    virtual int get_subrange_min_value() const = 0;

    /**
     * Set the subrange minimum value.
     * @param min_value the value to set.
     */
    virtual void set_subrange_min_value(const int min_value) = 0;

    /**
     * Get the subrange maximum value.
     * @return the value.
     */
    virtual int get_subrange_max_value() const = 0;

    /**
     * Set the subrange maximum value.
     * @param max_value the value to set.
     */
    virtual void set_subrange_max_value(const int max_value) = 0;

    /**
     * Get the vector of enumeration constants symbol table entries.
     * @return the vector.
     */
    virtual vector<SymTabEntry *> *get_enumeration_constants() const = 0;

    /**
     * Set the vector of enumeration constants symbol table entries.
     * @parm constants the vector to set.
     */
    virtual void set_enumeration_constants(vector<SymTabEntry *> *constants) = 0;

    /**
     * Get the array index data type.
     * @return the data type.
     */
    virtual TypeSpec *get_array_index_type() const = 0;

    /**
     * Set the array index data type.
     * @parm index_type the data type to set.
     */
    virtual void set_array_index_type(TypeSpec *index_type) = 0;

    /**
     * Get the array element data type.
     * @return the data type.
     */
    virtual TypeSpec *get_array_elmt_type() const = 0;

    /**
     * Set the array element data type.
     * @return elmt_type the data type to set.
     */
    virtual void set_array_elmt_type(TypeSpec *elmt_type) = 0;

    /**
     * Get the array element count.
     * @return the count.
     */
    virtual int get_array_elmt_count() const = 0;

    /**
     * Set the array element count.
     * @parm elmt_count the count to set.
     */
    virtual void set_array_elmt_count(const int elmt_count) = 0;

    /**
     * Get the record's symbol table.
     * @return the symbol table.
     */
    virtual SymTab *get_record_symtab() const = 0;

    /**
     * Set the record's symbol table.
     * @parm symtab the symbol table to set.
     */
    virtual void set_record_symtab(SymTab *symtab) = 0;
};

}}  // namespace wci::intermediate

#endif /* TYPESPEC_H_ */
