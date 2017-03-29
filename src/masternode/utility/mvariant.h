#ifndef MVARIANT_H
#define MVARIANT_H
#include<type_traits>
#include<utility>
#include<memory>
#include<cstdint>
#include"errcode.h"
namespace mocores
{
    template<class T>
    class VarTag
    {
        using type=T;
    };

    template<class U,class T,class ...Targs>
    class HasType
    {
    public:
        constexpr static bool value=false||HasType<U,Targs...>::value;
    };
    template<class U,class ...Targs>
    class HasType<U,U,Targs...>
    {
    public:
        constexpr static bool value=true||HasType<U,Targs...>::value;
    };
    template<class U,class T>
    class HasType<U,T>
    {
    public:
        constexpr static bool value=false;
    };
    template<class U>
    class HasType<U,U>
    {
    public:
        constexpr static bool value=true;
    };

    template<class U,class T,class ...Targs>
    class GetIndex
    {
    public:
        const static int index=GetIndex<U,Targs...>::index+1;
    };
    template<class U,class ...Targs>
    class GetIndex<U,U,Targs...>
    {
    public:
        const static int index=0;
    };
    template<class U,class T>
    class GetIndex<U,T>
    {
    public:
        const static int index=-1;
    };
    template<class U>
    class GetIndex<U,U>
    {
    public:
        const static int index=0;
    };

    template<class T,class ...Targs>
    class Destruct
    {
    public:
        static void destruct(int index,void * ptr)
        {
            if(index==0)
            {
                delete (static_cast<T *>(ptr));
            }
            else
            {
                Destruct<Targs...>::destruct(index-1,ptr);
            }
        }
    };
    template<class T>
    class Destruct<T>
    {
    public:
        static void destruct(int index,void * ptr)
        {
            if(index==0)
            {
                delete (static_cast<T *>(ptr));
            }
            else
            {
                throw "Can not find type.";
            }
        }
    };

    template<class T,class ...Targs>
    class Copy
    {
    public:
        static void copy(int index,void *& source,void *& to)
        {
            if(index==0)
            {
                if(source!=to)
                    to=new T(*(static_cast<T *>(source)));
            }
            else
            {
                Copy<Targs...>::copy(index-1,source,to);
            }
        }
    };
    template<class T>
    class Copy<T>
    {
    public:
        static void copy(int index,void *& source,void *& to)
        {
            if(index==0)
            {
                if(source!=to)
                    to=new T(*(static_cast<T *>(source)));
            }
            else
            {
                throw "Can not find type.";
            }
        }
    };


    template<class T,class ...Targs>
    class MVariant
    {
    public:
        MVariant()
        {
            data=new T();
            curindex=0;
        }
        template<class U>
        MVariant(const U & value)
        {
            if(HasType<U,T,Targs...>::value==true)
            {
                data=new U(value);
                curindex=GetIndex<U,T,Targs...>::index;
            }
            else
            {
                throw "Unknown type.";
            }
        }
        template<class U,class ...args>
        MVariant(MVariant<U,args...>& other)
        {
            Copy<U,args...>::copy(other.curindex,other.data,this->data);
            this->curindex=other.curindex;
        }

        template<class U,class ...args>
        MVariant& operator =(MVariant<U,args...>& other)
        {
            if(data!=nullptr)
            {
                Destruct<T,Targs...>::destruct(curindex,data);
            }
            Copy<U,args...>::copy(other.curindex,other.data,this->data);
            this->curindex=other.curindex;
        }

        virtual ~MVariant()
        {
            if(data!=nullptr)
            {
                Destruct<T,Targs...>::destruct(curindex,data);
            }
        }
        constexpr uint32_t index()const {return curindex;}

        template<class U>
        void operator =(const U& val)
        {
            if(data!=nullptr)
            {
                Destruct<T,Targs...>::destruct(curindex,data);
            }
            data=new U(val);
            curindex=GetIndex<U,T,Targs...>::index;
        }
        void * data;
        int curindex;
    };

    template <class T, class U,class... Types>
    T get(MVariant<U,Types...>& v)
    {
        if(GetIndex<T,U,Types...>::index==v.curindex)
        {
            return *(static_cast<T *>(v.data));
        }
        else
        {
            throw "Can not find the value.";
        }
    }

}


#endif // MVARIANT_H
