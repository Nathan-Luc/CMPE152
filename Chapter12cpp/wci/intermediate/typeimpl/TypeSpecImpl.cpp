/**
 * <h1>TypeSpecImpl</h1>
 *
 * <p>A Pascal type specification implementation.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include <string>
#include "TypeSpecImpl.h"
#include "../TypeSpec.h"
#include "../symtabimpl/Predefined.h"

namespace wci { namespace intermediate { namespace typeimpl {

using namespace std;
using namespace wci::intermediate;
using namespace wci::intermediate::symtabimpl;

bool TypeSpecImpl::INITIALIZED = false;

EnumMap<TypeFormImpl, string> TypeSpecImpl::TYPE_FORM_NAMES;
EnumMap<TypeKeyImpl,  string> TypeSpecImpl::TYPE_KEY_NAMES;

void TypeSpecImpl::initialize()
{
    if (INITIALIZED) return;

    vector<TypeFormImpl> form_keys =
    {
        TypeFormImpl::SCALAR,
        TypeFormImpl::ENUMERATION,
        TypeFormImpl::SUBRANGE,
        TypeFormImpl::ARRAY,
        TypeFormImpl::RECORD,
    };

    vector<string> form_names =
    {
        "scalar", "enumeration", "subrange", "array", "record",
    };

    for (int i = 0; i < form_keys.size(); i++)
    {
        TYPE_FORM_NAMES[form_keys[i]] = form_names[i];
    }

    INITIALIZED = true;
}

TypeSpecImpl::TypeSpecImpl() : form((TypeForm) -1), type_id(nullptr)
{
    initialize();
}

TypeSpecImpl::TypeSpecImpl(TypeForm form) : form(form), type_id(nullptr)
{
    initialize();
}

TypeSpecImpl::TypeSpecImpl(string value)
    : form((TypeForm) TF_ARRAY), type_id(nullptr)
{
    initialize();

    int length = value.length();
    content.array.elmt_type  = Predefined::char_type;
    content.array.elmt_count = length;
    content.array.index_type = new TypeSpecImpl((TypeForm) TF_SUBRANGE);
    content.array.index_type->set_base_type(Predefined::integer_type);
    content.array.index_type->set_subrange_min_value(1);
    content.array.index_type->set_subrange_max_value(length);
}

bool TypeSpecImpl::is_pascal_string()
{
    if (form == (TypeForm) TF_ARRAY)
    {
        return (content.array.elmt_type->base_type()  == Predefined::char_type)
            && (content.array.index_type->base_type() == Predefined::integer_type);
    }
    else
    {
        return false;
    }
}

/**
 * @return the base type of this type.
 */
TypeSpec *TypeSpecImpl::base_type()
{
    return form == (TypeForm) TF_SUBRANGE ? content.subrange.base_type : this;
}

}}}  // namespace wci::intermediate::typeimpl
