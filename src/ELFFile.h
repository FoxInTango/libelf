#ifndef _LIB_ELF_FILE_H_
#define _LIB_ELF_FILE_H_
#include <libcpp/libcpp.h>
EXTERN_C_BEGIN
namespaceBegin(foxintango)
class foxintangoAPI ELFFile{
public:
    ELFFile();
    ELFFile(const char* path);
    ~ELFFile();
public:
    int open(const char* path);
    /**
     * load to memory 
     */
    int load();
    /**
     * 1,类型判断
     * 2,加载数据段
     * 3,加载程序段
     * 4,加载依赖
     * 5,内部重定位
     */
};
namespaceEnd
EXTERN_C_END
#endif // !_LIB_ELF_FILE_H_
