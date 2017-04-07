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

    SqlWrapperFrom SqlWrapperSelect::distinct()
    {
        sql+=" distinct ";
        return SqlWrapperFrom(sql);
    }

    std::string SqlWrapperBase::get()
    {
        return this->sql+";";
    }

    SqlWrapperSelect SqlWrapperBase::select(const std::string &str)
    {
        sql="select "+str+" ";
        return sql;
    }

    SqlWrapperInsert SqlWrapperBase::insert()
    {
        return SqlWrapperInsert(sql);
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
        return "( "+lhs+" is not "+rhs+" )";
    }

    std::string SqlWrapperBase::between(const std::string &val, const std::string &lhs, const std::string &rhs)
    {
        return val+" between "+lhs+" and "+rhs+" ";
    }

    std::string SqlWrapperBase::like(const std::string &lhs, const std::string &rhs)
    {
        return lhs+" like "+rhs+" ";
    }

    SqlWrapperWhere SqlWrapperWhere::where(const std::string &str)
    {
        sql+="and( "+str+") ";
        return SqlWrapperWhere(sql);
    }

    SqlWrapperWhere SqlWrapperWhere::orwhere(const std::string &str)
    {
        sql+="or( "+str+") ";
        return SqlWrapperWhere(sql);
    }

    SqlWrapperEnd SqlWrapperWhere::orderby(const std::string &str)
    {
        sql+="order by "+str+" ";
        return SqlWrapperEnd(sql);
    }
    SqlWrapperValues SqlWrapperInto::values(const std::string &str)
    {
        sql+="values( "+str+" )";
        return SqlWrapperValues(sql);
    }

    SqlWrapperValues SqlWrapperInto::cols(const std::string &str)
    {
        sql+="( "+str+" )";
        return SqlWrapperValues(sql);
    }

    SqlWrapperValues SqlWrapperValues::values(const std::string &str)
    {
        sql+="values( "+str+" )";
        return SqlWrapperValues(sql);
    }



}

