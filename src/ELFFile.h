#ifndef _LIB_ELF_FILE_H_
#define _LIB_ELF_FILE_H_
#include <libcpp/libcpp.h>
EXTERN_C_BEGIN
namespaceBegin(foxintango)

#define ELF_NIDENT_SIZE (16)
class foxintangoAPI ELFIdent{
public:
    unsigned char m_magic[5];
    unsigned char m_bitwide;
    unsigned char m_endian;
    unsigned char m_version;
public:
    unsigned char* magic();
    unsigned char bitwide();
    unsigned char endian();
    unsigned char version();
};

class foxintangoAPI ELFHeader{
public:
    unsigned short m_type;
    unsigned short m_machine;
    unsigned short m_version;
    unsigned int   m_flags;
    unsigned short m_ehsize;
    unsigned short m_phentsize;
    unsigned short m_phnum;
    unsigned short m_shentsize;
    unsigned short m_shnum;
    unsigned short m_shstrndx;
};

class foxintangoAPI ELFSegment{};
class foxintangoAPI ELFSection{};

class foxintangoAPI ELFHeader32  :public ELFHeader  {
public:
    unsigned int m_entry;
    unsigned int m_phoff;
    unsigned int m_shoff;
};
class foxintangoAPI ELFSegment32 :public ELFSegment {};
class foxintangoAPI ELFSection32 :public ELFSection {};

class foxintangoAPI ELFHeader64  :public ELFHeader  {
public:
    unsigned long long m_entry;
    unsigned long long m_phoff;
    unsigned long long m_shoff;
};

class foxintangoAPI ELFSegment64 :public ELFSegment {};
class foxintangoAPI ELFSection64 :public ELFSection {};

class foxintangoAPI ELFFile{
public:
    ELFFile();
    ELFFile(const char* path);
    ~ELFFile();
public:
    ELFIdent ident;
    ELFHeader* header;
    Array<ELFSegment*> segments;
    Array<ELFSection*> sections;
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
