#ifndef RESULTSET_H
#define RESULTSET_H
#include<vector>
#include<string>
namespace mocores
{
    class SqlResultSet
    {
    public:
        SqlResultSet();
        std::vector<std::vector<std::string>> data;
    };
}


#endif // RESULTSET_H
