/*
    © 2016-2017 mocores
    This file is distributed under the MIT liscense.
    See LICENSE for details.
*/
#ifndef LOGGER_H
#define LOGGER_H

#include<string>
#include<queue>
#include<chrono>
#include<cassert>
#include<exception>
#include<ostream>

#include"logmsg.h"
#include"loglayout.h"
#include"logappender.h"
#include"../thread/mocores_mutex.h"
#include"../thread/mocores_thread.h"
#include"../thread/mocores_condition_variable.h"

namespace mocores
{
    /*!
     * \brief The Logger class
     */
    class Logger
    {
    public:
        using TimePoint=std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;
        Logger():running(false),log_thread(nullptr),appender(new ConsoleAppender){}
        virtual ~Logger()
        {
            delete log_thread;
            delete appender;
        }
        Logger(const Logger &other)=delete;
        Logger operator =(const Logger &other)=delete;
        void setName(const char * name);
        void setLayout(const LogLayout& _layout){layout=_layout;}
        bool configure(){return true;}
        bool configureFromMem(const char * settings){return true;}
        bool configureFromFile(const char * filepath){return true;}
        //
        void off(const std::string & msg)
        {
            mocores::UniqueLock<Mutex> lock(queue_mtx);
            LogMsg logmsg(LogLevel("OFF"),msg,mocores::this_thread::get_id());
            log_queue.push(logmsg);
        }

        void fatal(const std::string & msg)
        {
            mocores::UniqueLock<Mutex> lock(queue_mtx);
            LogMsg logmsg(LogLevel("FATAL"),msg,mocores::this_thread::get_id());
            log_queue.push(logmsg);
        }
        void error(const std::string & msg)
        {
            mocores::UniqueLock<Mutex> lock(queue_mtx);
            LogMsg logmsg(LogLevel("ERROR"),msg,mocores::this_thread::get_id());
            log_queue.push(logmsg);
        }
        void warn(const std::string & msg)
        {
            mocores::UniqueLock<Mutex> lock(queue_mtx);
            LogMsg logmsg(LogLevel("WARN"),msg,mocores::this_thread::get_id());
            log_queue.push(logmsg);
        }
        void info(const std::string & msg)
        {
            mocores::UniqueLock<Mutex> lock(queue_mtx);
            LogMsg logmsg(LogLevel("INFO"),msg,mocores::this_thread::get_id());
            log_queue.push(logmsg);
        }
        void debug(const std::string & msg)
        {
            mocores::UniqueLock<Mutex> lock(queue_mtx);
            LogMsg logmsg(LogLevel("DEBUG"),msg,mocores::this_thread::get_id());
            log_queue.push(logmsg);
        }
        void all(const std::string & msg)
        {
            mocores::UniqueLock<Mutex> lock(queue_mtx);
            LogMsg logmsg(LogLevel("ALL"),msg,mocores::this_thread::get_id());
            log_queue.push(logmsg);
        }

        void start()
        {
            assert(running==false);
            running=true;
            start_time=std::chrono::system_clock::now();
            layout.setStartTime(start_time);
            log_thread=new mocores::Thread(std::bind(&Logger::run, this));
        }
        void end()
        {
            {
              mocores::UniqueLock<mocores::Mutex> lock(queue_mtx);
              UNUSED(lock);
              running = false;
            }
            assert(log_thread!=nullptr);
            log_thread->join();
            delete log_thread;
            log_thread=nullptr;
        }

    protected:
        void run()
        {
            try
            {
              while (running)
              {
                  if(!log_queue.empty())
                  {
                      mocores::UniqueLock<Mutex> lock(queue_mtx);
                      UNUSED(lock);
                      appender->append(layout.getMsgText(log_queue.front()));
                      log_queue.pop();
                  }
              }
            }
            catch (const std::exception& ex)
            {
                std::cerr<<"exception caught in Logger %s\n"<<logger_name<<std::endl;
                std::cerr<<"reason: %s\n"<<ex.what()<<std::endl;
                abort();
            }
            catch (...)
            {
                std::cerr<<"unknown exception caught in Logger %s\n"<<logger_name<<std::endl;
                throw; // rethrow
            }
        }


        /*!
         * \brief setAppender
         * \param app
         * \note We will delete appender. The Appender must be created in heap.
         */
        void setAppender(LogAppender *app)
        {
            if(appender!=nullptr)
                delete appender;
            appender=app;
        }
    protected:
        std::string logger_name;
        std::queue<LogMsg> log_queue;
        mocores::Mutex queue_mtx;
        bool running;
        TimePoint start_time;
        mocores::Thread * log_thread;
        LogLayout layout;
        LogAppender *appender;
    };
}


#endif // LOGGER_H
