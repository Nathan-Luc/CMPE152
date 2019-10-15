/**
 * <h1>TypeFactory</h1>
 *
 * <p>A factory for creating type specifications.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#ifndef TYPEFACTORY_H_
#define TYPEFACTORY_H_

#include <string>
#include "TypeSpec.h"
#include "typeimpl/TypeSpecImpl.h"

namespace wci { namespace intermediate {

using namespace std;
using namespace wci::intermediate::typeimpl;

class TypeFactory
{
public:
    /**
     * Create a type specification of a given form.
     * @param form the form.
     * @return the type specification.
     */
    static TypeSpec *create_type(const TypeForm form)
    {
        return new TypeSpecImpl(form);
    }

    /**
     * Create a string type specification.
     * @param value the string value.
     * @return the type specification.
     */
    static TypeSpec *create_string_type(const string value)
    {
        return new TypeSpecImpl(value);
    }
};

}}  // namespace wci::intermediate

#endif /* TYPEFACTORY_H_ */
