#include "../minimal-ti.h"

struct Test1{
    union InnerUnion{
        int a;
        int b;
    };
};

namespace tst{
    enum Enum{};
}

int main() {
    static_assert(mti::GetName<Test1>() == "Test1");
    
    static_assert(mti::GetName<Test1::InnerUnion>() == "Test1::InnerUnion");

    using namespace tst;
    static_assert(mti::GetName<Enum>() == "tst::Enum");
    
    return 0;
}