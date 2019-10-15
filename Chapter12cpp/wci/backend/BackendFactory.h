/**
 * <h1>BackendFactory</h1>
 *
 * <p>A factory class that creates compiler and interpreter components.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#ifndef WCI_BACKEND_BACKENDFACTORY_H_
#define WCI_BACKEND_BACKENDFACTORY_H_

#include <string>
#include "Backend.h"
#include "compiler/CodeGenerator.h"
#include "interpreter/Executor.h"
#include "interpreter/Cell.h"
#include "../Object.h"
#include "../intermediate/TypeSpec.h"
#include "../intermediate/symtabimpl/Predefined.h"

namespace wci { namespace backend {

using namespace std;
using namespace wci::backend::compiler;
using namespace wci::backend::interpreter;
using namespace wci::intermediate::symtabimpl;

class BackendFactory
{
public:
    /**
     * Create a compiler or an interpreter back end component.
     * @param operation either "compile" or "execute"
     * @return a compiler or an interpreter back end component.
     * @throw a string message if an error occurred.
     */
	static Backend *create_backend(string operation) throw (string)
	{
	    if (operation == "compile")
	    {
	        return new CodeGenerator();
	    }
	    else if (operation == "execute")
	    {
	        return new Executor();
	    }
	    else
	    {
	        throw new string("Backend factory: Invalid operation '" +
	                         operation + "'");
	    }
	}

    /**
     * Return the default value for a data type.
     * @param typespec the data type.
     * @return the default value.
     */
    static Object default_value(TypeSpec *typespec)
    {
        typespec = typespec->base_type();

        if (typespec == Predefined::integer_type)
        {
            return 0;
        }
        else if (typespec == Predefined::real_type)
        {
            return 0.0f;
        }
        else if (typespec == Predefined::boolean_type)
        {
            return false;
        }
        else if (typespec == Predefined::char_type)
        {
            return '#';
        }
        else // string
        {
            return "#";
        }
    }
};

}} // namespace wci::backend

#endif /* WCI_BACKEND_BACKENDFACTORY_H_ */
