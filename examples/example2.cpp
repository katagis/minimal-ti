#include "../minimal-ti.h"
#include <iostream>

struct S1{
    struct StructInner1{
    };

    static mti::TypeId GetInnerId() {
        return mti::GetTypeId<StructInner1>();
    }
};

int main() {
    mti::TypeId id1 = S1::GetInnerId();
    mti::TypeId id2 = mti::GetTypeId<S1::StructInner1>();

    if (id1 == id2) { // Is true
        std::cout << "Success!\n";
        return 0;
    }

    return 1;
}