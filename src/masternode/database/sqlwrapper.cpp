#include "sqlwrapper.h"
namespace mocores
{

    SqlWrapperFrom SqlWrapperSelect::from(const std::string &str)
    {
        sql+="from "+str+" ";
        return SqlWrapperFrom(sql);
    }

    SqlWrapperWhere SqlWrapperFrom::where(const std::string &str)
    {
        sql+="where "+str+" ";
        return SqlWrapperWhere(sql);
    }

    std::string SqlWrapperBase::get()
    {
        return this->sql+";";
    }

    std::string SqlWrapperBase::equal(const std::string &lhs, const std::string &rhs)
    {
        return "( "+lhs+" == "+rhs+" )";
    }

    std::string SqlWrapperBase::notequal(const std::string &lhs, const std::string &rhs)
    {
        return "( "+lhs+" != "+rhs+" )";
    }

    std::string SqlWrapperBase::bt(const std::string &lhs, const std::string &rhs)
    {
        return"( "+lhs+" > "+rhs+" )";
    }

    std::string SqlWrapperBase::lt(const std::string &lhs, const std::string &rhs)
    {
        return"( "+lhs+" < "+rhs+" )";
    }

    std::string SqlWrapperBase::nbt(const std::string &lhs, const std::string &rhs)
    {
        return"( "+lhs+" <= "+rhs+" )";
    }

    std::string SqlWrapperBase::nlt(const std::string &lhs, const std::string &rhs)
    {
        return"( "+lhs+" >= "+rhs+" )";
    }

    std::string SqlWrapperBase::is(const std::string &lhs, const std::string &rhs)
    {
        return"( "+lhs+" is "+rhs+" )";
    }

    std::string SqlWrapperBase::isnot(const std::string &lhs, const std::string &rhs)
    {
        return"( "+lhs+" is not "+rhs+" )";
    }

    SqlWrapperSelect SqlWrapperBase::select(const std::string &str)
    {
        sql="select "+str+" ";
        return SqlWrapperSelect(sql);
    }

    SqlWrapperWhere SqlWrapperWhere::where(const std::string &str)
    {
        sql+="&&( "+str+") ";
        return SqlWrapperWhere(sql);
    }

    SqlWrapperWhere SqlWrapperWhere::orwhere(const std::string &str)
    {
        sql+="||( "+str+") ";
        return SqlWrapperWhere(sql);
    }


}

