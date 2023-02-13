#include <type_traits>
template<typename T> struct TIsPODType
{
    enum {Value = std::is_pod_v<T>};
};

template<typename T> struct ValueBase
{
    enum {NeedConstructor = !std::is_trivially_constructible_v<T> && !TIsPODType<T>::Value};
    enum {NeedDestructor = !std::is_trivially_destructible_v<T> && !TIsPODType<T>::Value};
};

class Sample
{
public:
    Sample(int arg):arg1(arg)
    {};
    ~Sample();
private:
    int arg1;
};