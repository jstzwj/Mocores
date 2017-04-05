#ifndef STRUTIL_H
#define STRUTIL_H
#include<string>
#include<cmath>
namespace mocores
{
    enum StrMatchMode
    {
        MOCORES_STRUTIL_CASE_SENSITIVE,
        MOCORES_STRUTIL_NON_CASE_SENSITIVE
    };

    class StrUtil
    {
    public:
        StrUtil();
        /*!
          *\brief   判断字符是否在某范围中
          * \note   begin included,end not.
          */
        static bool isInCharRange(char c,char min,char max);
        /*!
          *\brief   判断两字符是否相等
          */
        static bool isSameChar(char lhs,char rhs,StrMatchMode mode=MOCORES_STRUTIL_CASE_SENSITIVE);
        /*!
         * \brief  去除pos后空白
        */
        static void consumeSpace(const std::string &str,int &pos);
        /*!
         * \brief 判断pos后是否是某字符串
         * \note MOCORES_STRUTIL_CASE_SENSITIVE case-sensitive
         *       MOCORES_STRUTIL_NON_CASE_SENSITIVE non-case-sensitive
         */
        static bool isStr(const std::string &str, int &pos, const std::string &match_str,StrMatchMode mode=MOCORES_STRUTIL_CASE_SENSITIVE);
    };
}


#endif // STRUTIL_H
