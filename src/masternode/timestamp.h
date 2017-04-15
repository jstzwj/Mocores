#ifndef TIMESTAMP_H
#define TIMESTAMP_H
#include<cstdint>
namespace mocores
{
    class TimeStamp
    {
    public:
        TimeStamp();
    private:
        uint64_t timestamp;
    };
}

#endif // TIMESTAMP_H
