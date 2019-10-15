/**
 * <h1>Globals</h1>
 *
 * <p>Copyright (c) 2018 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include <string>
#include <algorithm>
#include <boost/lexical_cast.hpp>
#include "Object.h"

using namespace std;

bool Options::intermediate = false;
bool Options::xref         = false;
bool Options::lines        = false;
bool Options::assign       = false;
bool Options::fetch        = false;
bool Options::call         = false;
bool Options::returnn      = false;

/**
 * Return a copy of a string with all the letters shifted to upper case.
 * @param str the original string.
 * @return a copy of the string with shifted letters.
 */
string to_upper(const string str)
{
    string upper_case(str);
    transform(upper_case.begin(), upper_case.end(),
              upper_case.begin(), ::toupper);
    return upper_case;
}

/**
 * Return a copy of a string with all the letters shifted to lower case.
 * @param str the original string.
 * @return a copy of the string with shifted letters.
 */
string to_lower(const string str)
{
    string lower_case(str);
    transform(lower_case.begin(), lower_case.end(),
              lower_case.begin(), ::tolower);
    return lower_case;
}

/**
 * Return the string version of an object.
 * @param obj the object.
 * @return the string.
 */
string stringify(const Object& obj)
{
    auto& objtype = obj.type();

    if (objtype == typeid(int))
        return to_string(boost::any_cast<int>(obj));
    else if (objtype == typeid(float))
        return to_string(boost::any_cast<float>(obj));
    else if (objtype == typeid(bool))
        return to_string(boost::any_cast<bool>(obj));
    else if (objtype == typeid(string))
        return boost::any_cast<string>(obj);
    else if (objtype == typeid(char))
        return to_string(boost::any_cast<char>(obj));
    else
        return "";
}
