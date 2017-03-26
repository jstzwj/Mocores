#ifndef SQLRECORD_H
#define SQLRECORD_H
#include<vector>
#include"mvariant.h"
namespace mocores
{
    class SqlRecord
    {
    public:
        SqlRecord();
        std::vector<MVariant> record_data;
    };
}


#endif // SQLRECORD_H
