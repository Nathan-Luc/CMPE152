/**
 * <h1>Object</h1>
 *
 * <p>A generic data value.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#ifndef OBJECT_H_
#define OBJECT_H_

#include <unordered_set>
#include <unordered_map>
#include <initializer_list>
#include <typeinfo>
#include <boost/any.hpp>

#define Object boost::any
#define instanceof(v, t) (v.type() == typeid(t))
#define cast(v, t) boost::any_cast<t>(v)

std::string stringify(const Object& obj);
std::string to_upper(const std::string str);
std::string to_lower(const std::string str);

class Options
{
public:
    static bool intermediate, xref, lines, assign, fetch, call, returnn;
};

template<class E>
struct enumhash
{
public:
    size_t operator() (const E &e) const
    {
        return std::hash<int>()(static_cast<int>(e));
    }
};

template<class E>
class EnumSet : public std::unordered_set<E, enumhash<E>>
{
public:
    EnumSet() : std::unordered_set<E, enumhash<E>>() {}

    EnumSet(std::initializer_list<E> il)
        : std::unordered_set<E, enumhash<E>>(il) {}

    EnumSet& operator =(std::initializer_list<E> il)
    {
        std::unordered_set<E, enumhash<E>>::operator =(il);
        return *this;
    }
};

template<class E, class V>
class EnumMap : public std::unordered_map<E, V, enumhash<E>>
{
public:
    EnumMap() : std::unordered_map<E, V, enumhash<E>>() {}
};

template<class E, class V>
class StringMap : public std::unordered_map<std::string, V>
{
public:
    StringMap() : std::unordered_map<std::string, V>() {}
};

#endif /* OBJECT_H_ */
