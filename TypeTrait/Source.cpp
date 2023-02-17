#include "StlTypeTraits.h"


int main()
{
    bool needConstruct = ValueBase<ImplicitSample1>::NeedConstructor;
    needConstruct = ValueBase<ImplicitSample1>::NeedDestructor;

    needConstruct = ValueBase<ImplicitSample2>::NeedConstructor;
    needConstruct = ValueBase<ImplicitSample2>::NeedDestructor;

    needConstruct = ValueBase<PlicitSample1>::NeedConstructor;
    needConstruct = ValueBase<PlicitSample1>::NeedDestructor;

    needConstruct = ValueBase<PlicitSample2>::NeedConstructor;
    needConstruct = ValueBase<PlicitSample2>::NeedDestructor;

    needConstruct = ValueBase<VirtualSample>::NeedConstructor;
    needConstruct = ValueBase<VirtualSample>::NeedDestructor;
    return 0;
}