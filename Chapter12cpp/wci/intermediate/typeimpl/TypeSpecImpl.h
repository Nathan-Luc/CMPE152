/**
 * <h1>TypeSpecImpl</h1>
 *
 * <p>A Pascal type specification implementation.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#ifndef TYPESPECIMPL_H_
#define TYPESPECIMPL_H_

#include <string>
#include "../TypeSpec.h"

namespace wci { namespace intermediate { namespace typeimpl {

using namespace std;

/**
 * Type specification form implementation
 */
enum class TypeFormImpl
{
    SCALAR, ENUMERATION, SUBRANGE, ARRAY, RECORD,
};

constexpr TypeFormImpl TF_SCALAR = TypeFormImpl::SCALAR;
constexpr TypeFormImpl TF_ENUMERATION = TypeFormImpl::ENUMERATION;
constexpr TypeFormImpl TF_SUBRANGE = TypeFormImpl::SUBRANGE;
constexpr TypeFormImpl TF_ARRAY = TypeFormImpl::ARRAY;
constexpr TypeFormImpl TF_RECORD = TypeFormImpl::RECORD;

/**
 * Type specification key implementation
 */
enum class TypeKeyImpl
{
    // Enumeration
    ENUMERATION_CONSTANTS,

    // Subrange
    SUBRANGE_BASE_TYPE, SUBRANGE_MIN_VALUE, SUBRANGE_MAX_VALUE,

    // Array
    ARRAY_INDEX_TYPE, ARRAY_ELEMENT_TYPE, ARRAY_ELEMENT_COUNT,

    // Record
    RECORD_SYMTAB,
};

constexpr TypeKeyImpl ENUMERATION_CONSTANTS = TypeKeyImpl::ENUMERATION_CONSTANTS;
constexpr TypeKeyImpl SUBRANGE_BASE_TYPE = TypeKeyImpl::SUBRANGE_BASE_TYPE;
constexpr TypeKeyImpl SUBRANGE_MIN_VALUE = TypeKeyImpl::SUBRANGE_MIN_VALUE;
constexpr TypeKeyImpl SUBRANGE_MAX_VALUE = TypeKeyImpl::SUBRANGE_MAX_VALUE;
constexpr TypeKeyImpl ARRAY_INDEX_TYPE = TypeKeyImpl::ARRAY_INDEX_TYPE;
constexpr TypeKeyImpl ARRAY_ELEMENT_TYPE = TypeKeyImpl::ARRAY_ELEMENT_TYPE;
constexpr TypeKeyImpl ARRAY_ELEMENT_COUNT = TypeKeyImpl::ARRAY_ELEMENT_COUNT;
constexpr TypeKeyImpl RECORD_SYMTAB = TypeKeyImpl::RECORD_SYMTAB;

typedef union
{
    struct
    {
        vector<SymTabEntry *> *constants;
    } enumeration;

    struct
    {
        TypeSpec *base_type;
        int min_value;
        int max_value;
    } subrange;

    struct
    {
        TypeSpec *index_type;
        TypeSpec *elmt_type;
        int elmt_count;
    } array;

    struct
    {
        SymTab *symtab;
    } record;
} TypeContent;

class TypeSpecImpl : public TypeSpec
{
public:
    /**
     * Constructor.
     * @param form the type form.
     */
    TypeSpecImpl();

    /**
     * Constructor.
     * @param form the type form.
     */
    TypeSpecImpl(TypeForm form);

    /**
     * Constructor.
     * @param value a string value.
     */
    TypeSpecImpl(string value);

    /**
     * Destructor.
     */
    ~TypeSpecImpl() {}

    /**
     * Getter
     * @return the type form.
     */
    TypeForm get_form() const { return form; }

    /**
     * Getter.
     * @return the type identifier (symbol table entry).
     */
    SymTabEntry *get_identifier() const { return type_id; }

    /**
     * Setter.
     * @param id the type identifier (symbol table entry).
     */
    void set_identifier(SymTabEntry *id) { type_id = id; }

    /**
     * Implementation of wci::intermediate::TypeSpec.
     * @return true if this is a Pascal string type.
     */
    bool is_pascal_string();

    /**
     * Implementation of wci::intermediate::TypeSpec.
     * @return the base type of this type.
     */
    TypeSpec *base_type();

    /**
     * Set the subrange base type.
     * @param base_type the base type to set.
     */
    void set_base_type(TypeSpec *base_type)
    {
        content.subrange.base_type = base_type;
    }

    /**
     * Get the subrange minimum value.
     * @return the value.
     */
    int get_subrange_min_value() const { return content.subrange.min_value; }

    /**
     * Set the subrange minimum value.
     * @param min_value the value to set.
     */
    void set_subrange_min_value(const int min_value)
    {
        content.subrange.min_value = min_value;
    }

    /**
     * Get the subrange maximum value.
     * @return the value.
     */
    int get_subrange_max_value() const { return content.subrange.max_value; }

    /**
     * Set the subrange maximum value.
     * @param max_value the value to set.
     */
    void set_subrange_max_value(const int max_value)
    {
        content.subrange.max_value = max_value;
    }

    /**
     * Get the vector of enumeration constants symbol table entries.
     * @return the vector.
     */
    vector<SymTabEntry *> *get_enumeration_constants() const
    {
        return content.enumeration.constants;
    }

    /**
     * Set the vector of enumeration constants symbol table entries.
     * @parm constants the vector to set.
     */
    void set_enumeration_constants(vector<SymTabEntry *> *constants)
    {
        content.enumeration.constants = constants;
    }

    /**
     * Get the array index data type.
     * @return the data type.
     */
    TypeSpec *get_array_index_type() const
    {
        return content.array.index_type;
    }

    /**
     * Set the array index data type.
     * @parm index_type the data type to set.
     */
    void set_array_index_type(TypeSpec *index_type)
    {
        content.array.index_type = index_type;
    }

    /**
     * Get the array element data type.
     * @return the data type.
     */
    TypeSpec *get_array_elmt_type() const
    {
        return content.array.elmt_type;
    }

    /**
     * Set the array element data type.
     * @return elmt_type the data type to set.
     */
    void set_array_elmt_type(TypeSpec *elmt_type)
    {
        content.array.elmt_type = elmt_type;
    }

    /**
     * Get the array element count.
     * @return the count.
     */
    int get_array_elmt_count() const
    {
        return content.array.elmt_count;
    }

    /**
     * Set the array element count.
     * @parm elmt_count the count to set.
     */
    void set_array_elmt_count(const int elmt_count)
    {
        content.array.elmt_count = elmt_count;
    }

    /**
     * Get the record's symbol table.
     * @return the symbol table.
     */
    SymTab *get_record_symtab() const { return content.record.symtab; }

    /**
     * Set the record's symbol table.
     * @parm symtab the symbol table to set.
     */
    void set_record_symtab(SymTab *symtab)
    {
        content.record.symtab = symtab;
    }

    static EnumMap<TypeFormImpl, string> TYPE_FORM_NAMES;
    static EnumMap<TypeKeyImpl,  string> TYPE_KEY_NAMES;

private:
    TypeForm form;
    SymTabEntry *type_id;  // type identifier
    TypeContent content;

    static bool INITIALIZED;

    /**
     * Initialize the static maps.
     */
    static void initialize();
};

}}}  // namespace wci::intermediate::typeimpl

#endif /* TYPESPECIMPL_H_ */
