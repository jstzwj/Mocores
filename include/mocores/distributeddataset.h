#ifndef DISTRIBUTEDDATASET_H
#define DISTRIBUTEDDATASET_H

#include<cstdint>

#include"filesystem/file.h"
namespace mocores
{
    class DistributedDataSet
    {
    public:
        DistributedDataSet();
    protected:
        /*! 是否被缓存 */
        int isBuffered;
        /*! 缓存最大大小 */
        uint32_t maxBufferLen;
        /*! 缓存 */
        uint8_t * buffer;
        /*! dds文件 */
        File * ddsFile;
    };
}


#endif // DISTRIBUTEDDATASET_H
