/**
 * <h1>RuntimeStackImpl</h1>
 *
 * <p>The interpreter's runtime stack.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#ifndef RUNTIMESTACKIMPL_H_
#define RUNTIMESTACKIMPL_H_

#include <string>
#include <vector>
#include "../RuntimeStack.h"
#include "../RuntimeDisplay.h"
#include "../ActivationRecord.h"

namespace wci { namespace backend { namespace interpreter { namespace memoryimpl {

using namespace wci;
using namespace wci::backend::interpreter;

class RuntimeStackImpl : public RuntimeStack
{
public:
    /**
     * Constructor.
     */
    RuntimeStackImpl();

    /**
     * Destructor.
     */
    ~RuntimeStackImpl()
    {
        delete display;
    }

    /**
     * @return an array list of the activation records on the stack.
     */
    vector<ActivationRecord *> *records() { return &stack; }

    /**
     * Get the topmost activation record at a given nesting level.
     * @param nesting_level the nesting level.
     * @return the activation record.
     */
    ActivationRecord *get_topmost(const int nesting_level) const
    {
        return display->get_activation_record(nesting_level);
    }

    /**
     * @return the current nesting level.
     */
    int current_nesting_level() const
    {
        int top_index = stack.size() - 1;
        return top_index >= 0 ? stack[top_index]->get_nesting_level() : -1;
    }

    /**
     * Push an activation record onto the stack for a routine being called.
     * @param ar the activation record to push.
     */
    void push(ActivationRecord *ar)
    {
        int nesting_level = ar->get_nesting_level();

        stack.push_back(ar);
        display->call_update(nesting_level, ar);
    }

    /**
     * Pop an activation record off the stack for a returning routine.
     */
    void pop()
    {
        display->return_update(current_nesting_level());
        stack.erase(stack.begin() + stack.size() - 1);
    }

private:
    vector<ActivationRecord *> stack;  // runtime stack
    RuntimeDisplay *display;           // runtime display
};

}}}}  // namespace wci::backend::interpreter::memoryimpl

#endif /* RUNTIMESTACKIMPL_H_ */
