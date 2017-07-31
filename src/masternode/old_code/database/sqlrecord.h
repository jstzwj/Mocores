#ifndef SQLRECORD_H
#define SQLRECORD_H
#include<vector>
#include<string>
#include"../utility/mvariant.h"

namespace mocores
{
    /*!
     * \brief Sql basic value.
     */
    using SqlType=MVariant<int,double,std::string>;
    /*!
      * \brief Sql type conversion.
      *
      */
    inline double parseDouble(const std::string &str){return std::stod(str);}
    inline int parseInt(const std::string &str){return std::stoi(str);}
    inline long parseLong(const std::string &str){return std::stol(str);}
    inline long double parseLongDouble(const std::string &str){return std::stold(str);}
    inline long long parseLongLong(const std::string &str){return std::stoll(str);}
    inline float parseFloat(const std::string &str){return std::stof(str);}
    /*!
     * \brief Represents a record in sql result sets.
     */
    class SqlRecord:public std::vector<std::string>
    {
    public:
        std::vector<bool> isNull;
    };
}


#endif // SQLRECORD_H
