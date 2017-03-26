#ifndef MVARIANT_H
#define MVARIANT_H
#include<type_traits>
#include<utility>
#include<cstdint>
#include"errcode.h"
namespace mocores
{

    template<class T,class ...Targs>
    class MVariant:public MVariant<Targs...>
    {
    public:
        MVariant():data(nullptr){}
        MVariant(const T & value)
        {
            data=new T(value);
            curindex=type_index;
        }

        ~MVariant()
        {
            delete data;
        }
        constexpr uint32_t index()const {return curindex;}
        T& get()
        {
            if(data!=nullptr)
                return *data;
            else
                throw MOCORES_VARIANT_EMPTY;
        }
        void set(const T& val)
        {
            if(data!=nullptr)
                *data=val;
            else
                throw MOCORES_VARIANT_EMPTY;
        }
    protected:
        T * data;
        static uint32_t curindex;
        constexpr static uint32_t type_index=MVariant<Targs...>::type_index+1;
    };


    template<class T>
    class MVariant<T>
    {
    public:
        MVariant():data(nullptr){}
        MVariant(const T & value)
        {
            data=new T(value);
            curindex=type_index;
        }

        ~MVariant()
        {
            delete data;
        }
        constexpr uint32_t index()const {return curindex;}
        T& get()
        {
            if(data!=nullptr)
                return *data;
            else
                throw MOCORES_VARIANT_EMPTY;
        }
        void set(const T& val)
        {
            if(data!=nullptr)
                *data=val;
            else
                throw MOCORES_VARIANT_EMPTY;
        }
    protected:
        T * data;
        static uint32_t curindex;
        constexpr static uint32_t type_index=0;
    };


    template <class T, class... Types>
    constexpr T& get(MVariant<Types...>& v){return v.get<T>();}
    template <class T, class... Types>
    constexpr T&& get(MVariant<Types...>&& v){return std::move(v.get<T>());}
}


#endif // MVARIANT_H
