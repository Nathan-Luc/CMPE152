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
#include "../Object.h"

namespace wci { namespace backend {

using namespace std;
using namespace wci::backend::compiler;
using namespace wci::backend::interpreter;

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
};

}} // namespace wci::backend

#endif /* WCI_BACKEND_BACKENDFACTORY_H_ */
