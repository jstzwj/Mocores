#ifndef SINGLETON_H
#define SINGLETON_H

#include<atomic>
#include<functional>

#include"mocores_mutex.h"
#include"mocores_thread.h"

namespace mocores
{
    template<class T>
    class Singleton
    {
    public:
        Singleton()=delete;
        ~Singleton();
        Singleton(const Singleton &other)=delete;
        Singleton & operator =(const Singleton &other)=delete;
        static T& getInstance()
        {
            static std::once_flag oc;
            std::call_once(oc,[&]{value=new T();});
            return *value;
        }
     private:
        static T* value;
    };
}


#endif // SINGLETON_H
