#ifndef SINGLETON_H
#define SINGLETON_H

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
        static T& instance()
        {
          pthread_once(&ponce_, &Singleton::init);
          assert(value_ != NULL);
          return *value_;
        }

     private:
      static void init()
      {
        value_ = new T();
        if (!detail::has_no_destroy<T>::value)
        {
          ::atexit(destroy);
        }
      }

      static void destroy()
      {
        typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
        T_must_be_complete_type dummy; (void) dummy;

        delete value_;
        value_ = NULL;
      }

     private:
      static pthread_once_t ponce_;
      static T*             value_;
    };
}


#endif // SINGLETON_H
