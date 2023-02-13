#include "StlTypeTraits.h"


int main()
{
    bool needConstruct = ValueBase<Sample>::NeedConstructor;
    return 0;
}