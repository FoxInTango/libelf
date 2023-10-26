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
     * 1,�����ж�
     * 2,�������ݶ�
     * 3,���س����
     * 4,��������
     * 5,�ڲ��ض�λ
     */
};
namespaceEnd
EXTERN_C_END
#endif // !_LIB_ELF_FILE_H_
