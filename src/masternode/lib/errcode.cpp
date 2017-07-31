#include "errcode.h"

namespace mocores
{
    std::string ErrCode::errmsg="";

    ErrCode::ErrCode()
    {

    }

    void ErrCode::setErrMsg(const std::string &str)
    {
        errmsg=str;
    }

    std::string ErrCode::getErrMsg()
    {
        return errmsg;
    }
}

