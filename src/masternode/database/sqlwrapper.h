#ifndef SQLWRAPPER_H
#define SQLWRAPPER_H

#include<string>

namespace mocores
{
    class SqlWrapperSelect;
    class SqlWrapperBase
    {
    public:
        SqlWrapperBase():sql(){}
        SqlWrapperBase(const std::string & str):sql(str){}
        /*!
         *  \brief get
         */
        std::string get();
        /*!
         *  \brief sql header
         */
        SqlWrapperSelect select(const std::string& str);
        /*!
         *  \brief comparasion
         */
        static std::string equal(const std::string& lhs,const std::string& rhs);
        static std::string notequal(const std::string& lhs,const std::string& rhs);
        static std::string bt(const std::string& lhs,const std::string& rhs);
        static std::string lt(const std::string& lhs,const std::string& rhs);
        static std::string nbt(const std::string& lhs,const std::string& rhs);
        static std::string nlt(const std::string& lhs,const std::string& rhs);
        static std::string is(const std::string& lhs,const std::string& rhs);
        static std::string isnot(const std::string& lhs,const std::string& rhs);
    protected:
        std::string sql;
    };

    class SqlWrapperWhere:public SqlWrapperBase
    {
    public:
        SqlWrapperWhere(const std::string & str):SqlWrapperBase(str){}
        /*!
         *  \brief where
         */
        SqlWrapperWhere where(const std::string& str);
        /*!
         *  \brief orwhere
         */
        SqlWrapperWhere orwhere(const std::string& str);
    };

    class SqlWrapperFrom:public SqlWrapperBase
    {
    public:
        SqlWrapperFrom(const std::string & str):SqlWrapperBase(str){}
        /*!
         *  \brief where
         */
        SqlWrapperWhere where(const std::string& str);
    };


    class SqlWrapperSelect:public SqlWrapperBase
    {
    public:
        SqlWrapperSelect(const std::string & str):SqlWrapperBase(str){}
        /*!
         *  \brief sql table and db
         */
        SqlWrapperFrom from(const std::string& str);
    };

    using SqlWrapper=SqlWrapperBase;

}


#endif // SQLWRAPPER_H
