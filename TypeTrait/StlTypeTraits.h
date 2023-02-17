#include <type_traits>

/*
* Some classes don't need constructors, so here is the research on whether the class needs a constructor
* https://stackoverflow.com/questions/7131983/in-which-cases-there-is-no-constructor-at-all-even-a-default-constructor
*/

/*
* trivial type
*  1. No custom constructor (but you can customize the no-argument constructor with default modification)
*  2. No assignment operator function
*  3. No virtual functions
*  4. No virtual base class
* standard layout type
*  1. All non-static members have the same access rights
*  2. The derived class has no non-static members, and at most one base class has non-static data members or a base class without non-static data members
*  3. The type of the first non-static member in the class is different from the base class type
*  4. All non-static members conform to the standard layout, and their base classes also conform to the standard layout
*  5. No virtual functions
*  6. No virtual base class
*/


/*
* Determine whether a type is an ordinary old data type (that is, a type supported by C language)
* Conditions (satisfied at the same time):
* 1. This class is a trivial type
* 2. This class is a standard layout type
*/
template<typename T> struct TIsPODType
{
    enum {Value = std::is_pod_v<T>};
};

/*
* is_trivially_constructible: https://cplusplus.com/reference/type_traits/is_trivially_default_constructible/
*  1. uses the implicitly defined default constructor.
*  2. has no virtual members.
*  3. has no non-static data members with brace- or equal- initializers.
*  4. its base class and non-static data members (if any) are themselves also trivially default constructible types. 
* 
* is_trivially_destructible: https://cplusplus.com/reference/type_traits/is_trivially_destructible/
*  1. uses the implicitly defined destructor.
*  2. the destructor is not virtual.
*  3. its base class and non-static data members (if any) are themselves also trivially destructible types.
*/


template<typename T> struct ValueBase
{
    enum {NeedConstructor = !std::is_trivially_constructible_v<T> && !TIsPODType<T>::Value};
    enum {NeedDestructor = !std::is_trivially_destructible_v<T> && !TIsPODType<T>::Value};
};

/*
* destructor related only
*/

class ImplicitSample1
{

};

class ImplicitSample2
{
public:
    ImplicitSample2() = default;
    ~ImplicitSample2() = default;
};

class PlicitSample1
{
public:
    PlicitSample1() {};
    ~PlicitSample1() {};
};

class PlicitSample2
{
public:
    PlicitSample2(int args1):m_args1(args1) {};
    ~PlicitSample2() {};
private:
    int m_args1;
};

class VirtualSample
{
public:
    virtual void func() {};
};