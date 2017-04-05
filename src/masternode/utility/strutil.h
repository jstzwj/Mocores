#ifndef STRUTIL_H
#define STRUTIL_H
#include<string>
namespace mocores
{
    class StrUtil
    {
    public:
        StrUtil();
        /*! 去除pos后空白*/
        static void consumeSpace(const std::string &str,int &pos);
        /*! 判断pos后是否是某字符串*/
        static bool isStr(const std::string &str, int &pos, const std::string &match_str);
    };
}


#endif // STRUTIL_H
