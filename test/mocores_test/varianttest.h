#ifndef VARIANTTEST_H
#define VARIANTTEST_H
#include"../catch/catch.hpp"
#include"../../src/masternode/mvariant.h"

template<class ...Targs>
class VariantSetAndGet
{
public:
    template<class T>
    static T setAndGet(T data)
    {
        mocores::MVariant<Targs...> tmp;
        tmp=data;
        return mocores::get<T>(tmp);
    }
};



TEST_CASE( "MVariant set and get", "int double bool" ) {
    REQUIRE( (VariantSetAndGet<int,double>::setAndGet(1)) == 1 );
    REQUIRE( (VariantSetAndGet<bool,double>::setAndGet(true)) == true );
    REQUIRE( (VariantSetAndGet<int,double>::setAndGet(1.0)) == 1.0 );
}



#endif // VARIANTTEST_H
