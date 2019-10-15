/**
 * <h1>StatementExecutor</h1>
 *
 * <p>Execute a statement.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include "StatementExecutor.h"
#include "CompoundExecutor.h"
#include "AssignmentExecutor.h"
#include "LoopExecutor.h"
#include "IfExecutor.h"
#include "SelectExecutor.h"
#include "CallExecutor.h"
#include "../Executor.h"
#include "../Cell.h"
#include "../MemoryFactory.h"
#include "../RuntimeError.h"
#include "../memoryimpl/MemoryMapImpl.h"
#include "../../../Object.h"
#include "../../../intermediate/TypeSpec.h"
#include "../../../intermediate/ICodeNode.h"
#include "../../../intermediate/symtabimpl/Predefined.h"
#include "../../../intermediate/icodeimpl/ICodeNodeImpl.h"
#include "../../../intermediate/typeimpl/TypeSpecImpl.h"
#include "../../../message/Message.h"

namespace wci { namespace backend { namespace interpreter { namespace executors {

using namespace std;
using namespace wci;
using namespace wci::backend::interpreter;
using namespace wci::backend::interpreter::memoryimpl;
using namespace wci::intermediate;
using namespace wci::intermediate::symtabimpl;
using namespace wci::intermediate::icodeimpl;
using namespace wci::intermediate::typeimpl;
using namespace wci::message;

Message StatementExecutor::AT_LINE_MESSAGE(AT_LINE);
Message StatementExecutor::ASSIGN_MESSAGE(ASSIGN);
Message StatementExecutor::FETCH_MESSAGE(FETCH);
Message StatementExecutor::CALL_MESSAGE(CALL);
Message StatementExecutor::RETURN_MESSAGE(RETURN);

Object StatementExecutor::execute(ICodeNode *node)
{
    ICodeNodeTypeImpl node_type = (ICodeNodeTypeImpl) node->get_type();

    // Send a message about the current source line.
    if (Options::lines) send_at_line_message(node);

    switch (node_type)
    {
        case NT_COMPOUND:
        {
            CompoundExecutor compound_executor(this);
            return compound_executor.execute(node);
        }

        case NT_ASSIGN:
        {
            AssignmentExecutor assignment_executor(this);
            return assignment_executor.execute(node);
        }

        case NT_LOOP:
        {
            LoopExecutor loop_executor(this);
            return loop_executor.execute(node);
        }

        case NT_IF:
        {
            IfExecutor if_executor(this);
            return if_executor.execute(node);
        }

        case NT_SELECT:
        {
            SelectExecutor select_executor(this);
            return select_executor.execute(node);
        }

        case NT_CALL:
        {
            CallExecutor call_executor(this);
            return call_executor.execute(node);
        }

        case NT_NO_OP: return Object();  // empty

        default:
        {
            error_handler.flag(node, UNIMPLEMENTED_FEATURE, this);
            return Object();  // empty
        }
    }
}

Object StatementExecutor::to_pascal(TypeSpec *target_typespec,
                                    const Object& java_value)
{
    if (java_value.empty()) return java_value;

    if (instanceof(java_value, string))
    {
        string value = cast(java_value, string);

        if (target_typespec == Predefined::char_type)
        {
            return value[0];  // Pascal character.
        }
        else if (target_typespec->is_pascal_string())
        {
            int length = value.length();
            vector<Cell *> *array = new vector<Cell *>;
            array->reserve(length);

            // Build an array of characters.
            for (int i = 0; i < length; ++i)
            {
                char ch = value[i];
                array->push_back(MemoryFactory::create_cell(ch));
            }

            return array;  // Pascal string (array of characters).
        }
    }

    return java_value;
}

Object StatementExecutor::to_java(TypeSpec *target_typespec,
                                  const Object& pascal_value,
                                  ICodeNode *node)
{
    if (instanceof(pascal_value, vector<Cell *>*))
    {
        vector<Cell *> *array = cast(pascal_value, vector<Cell *>*);
        Object *element = (*array)[0]->get_value();

        if (instanceof((*element), char))
        {
            int length = array->size();

            // Build a Java string.
            string str = "";
            for (int i = 0; i < length; i++)
            {
                char ch = cast((*(*array)[i]->get_value()), char);
                str += ch;
            }

            return str;  // C++ string
        }
        else return pascal_value;
    }
    else return pascal_value;
}

Object StatementExecutor::copy_of(Object cell_value, ICodeNode *node)
{
    if (cell_value.empty()) return Object();  // empty

    if (instanceof(cell_value, vector<Cell *>*))
    {
        return copy_array(cell_value, node);
    }
    else if (instanceof(cell_value, MemoryMapImpl*))
    {
        return copy_record(cell_value, node);
    }
    else
    {
        return cell_value;
    }
}

Object StatementExecutor::copy_array(Object& array_value, ICodeNode *node)
{
    vector<Cell *> *copy_array = new vector<Cell *>;

    if (!array_value.empty())
    {
        vector<Cell *> *orig_array = cast(array_value, vector<Cell *>*);
        int size = orig_array->size();

        copy_array->reserve(size);
        for (int i = 0; i < size; i++)
        {
            Object copy_value = copy_of(*((*orig_array)[i]->get_value()), node);
            copy_array->push_back(MemoryFactory::create_cell(copy_value));
        }
    }
    else
    {
        error_handler.flag(node, UNINITIALIZED_VALUE, this);
    }

    return copy_array;
}

Object StatementExecutor::copy_record(Object& record_value, ICodeNode *node)
{
    MemoryMapImpl *copy_map = new MemoryMapImpl();

    if (!record_value.empty())
    {
        MemoryMapImpl *orig_map = cast(record_value, MemoryMapImpl*);
        StringMap<string, Cell *>* orig_contents = orig_map->get_contents();
        StringMap<string, Cell *>* copy_contents = copy_map->get_contents();
        StringMap<string, Cell *>::iterator it;

        for (it = orig_contents->begin(); it != orig_contents->end(); it++)
        {
            Object copy_value = copy_of(*(it->second->get_value()), node);
            Cell *copy_cell = MemoryFactory::create_cell(copy_value);
            pair<string, Cell *> pair(it->first, copy_cell);
            copy_contents->insert(pair);
        }
    }
    else
    {
        error_handler.flag(node, UNINITIALIZED_VALUE, this);
    }

    return copy_map;
}

void StatementExecutor::check_range(
             ICodeNode *node, TypeSpec *typespec, Object& cell_value)
{
    if (typespec->get_form() == (TypeForm) TF_SUBRANGE)
    {
        int min_value = typespec->get_subrange_min_value();
        int max_value = typespec->get_subrange_max_value();
        int value = cast(cell_value, int);

        if (value < min_value)
        {
            error_handler.flag(node, VALUE_RANGE, this);
            cell_value = min_value;
        }
        else if (value > max_value)
        {
            error_handler.flag(node, VALUE_RANGE, this);
            cell_value = max_value;
        }
    }
}

string StatementExecutor::display_value(const Object& cell_value) const
{
    string value_str =
          cell_value.empty()                     ? "<?>"
        : instanceof(cell_value, Cell*)          ? "<reference>"
        : instanceof(cell_value, Cell**)         ? "<array>"
        : instanceof(cell_value, MemoryMapImpl*) ? "<record>"
                                                 : stringify(cell_value);
    return value_str;
}

void StatementExecutor::send_at_line_message(ICodeNode *node)
{
    AT_LINE_MESSAGE.line_number = node->get_line_number();
    send_message(AT_LINE_MESSAGE);
}

void StatementExecutor::send_assign_message(ICodeNode *node,
                                            string& variable_name,
                                            Object& cell_value)
{
    string value_str = display_value(cell_value);
    ASSIGN_MESSAGE.line_number = get_line_number(node);
    ASSIGN_MESSAGE.content.assign.variable_name = variable_name.c_str();
    ASSIGN_MESSAGE.content.assign.result_value = value_str.c_str();
    send_message(ASSIGN_MESSAGE);
}

void StatementExecutor::send_fetch_message(ICodeNode *node,
                                           string& variable_name,
                                           Object& cell_value)
{
    string value_str = display_value(cell_value);
    FETCH_MESSAGE.line_number = get_line_number(node);
    FETCH_MESSAGE.content.fetch.variable_name = variable_name.c_str();
    FETCH_MESSAGE.content.fetch.value = value_str.c_str();
    send_message(FETCH_MESSAGE);
}

void StatementExecutor::send_call_message(ICodeNode *node,
                                          string& routine_name)
{
    CALL_MESSAGE.line_number = get_line_number(node);
    CALL_MESSAGE.content.call.routine_name = routine_name.c_str();
    send_message(CALL_MESSAGE);
}

void StatementExecutor::send_return_message(ICodeNode *node,
                                            string& routine_name)
{
    RETURN_MESSAGE.line_number = get_line_number(node);
    RETURN_MESSAGE.content.returnn.routine_name = routine_name.c_str();
    send_message(RETURN_MESSAGE);
}

int StatementExecutor::get_line_number(ICodeNode *node)
{
    // Go up the parent links to look for a line number.
    while ((node != nullptr) &&
           (node->get_line_number() == 0))
    {
        node = node->get_parent();
    }

    return node->get_line_number();
}

}}}}  // namespace wci::backend::interpreter::executors
