#ifndef MERROROR_H
#define MERROROR_H
#include"../errcode.h"
namespace mocores
{
    template<class T,class ErrorType=ErrorCode>
    class MErrorOr
    {
    public:
        MErrorOr();
    };
}


#endif // MERROROR_H
