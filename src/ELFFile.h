#ifndef _LIB_ELF_FILE_H_
#define _LIB_ELF_FILE_H_
#include <libcpp/libcpp.h>

EXTERN_C_BEGIN
namespaceBegin(foxintango)

class foxintangoAPI ELFIdent{
public:
    unsigned char m_magic[4];
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

class foxintangoAPI ELFStringTable{
public:
    unsigned char* m_content;
    Array<unsigned char*> m_strings;
};
/** 64位问题可能由内存对齐问题导致
 *  逐成员读文件较为保险 
 */

class foxintangoAPI ELFSegment{
public:
    unsigned int	m_type;
    unsigned int	m_flags;
};
class foxintangoAPI ELFSection{
public:
    unsigned int	m_name;
    unsigned int	m_type;
    unsigned int	m_link;
    unsigned int	m_info;
};

class foxintangoAPI ELFHeader32  :public ELFHeader  {
public:
    unsigned int m_entry;
    unsigned int m_phoff;
    unsigned int m_shoff;
};
class foxintangoAPI ELFSegment32 :public ELFSegment {
public:
    unsigned int	m_offset;
    unsigned int	m_vaddr;
    unsigned int	m_paddr;
    unsigned int	m_filesz;
    unsigned int	m_memsz;
    unsigned int	m_align;
};
class foxintangoAPI ELFSection32 :public ELFSection {
public:
    unsigned int	m_flags;
    unsigned int	m_addr;
    unsigned int	m_offset;
    unsigned int	m_size;
    unsigned int	m_addralign;
    unsigned int	m_entsize;
};

class foxintangoAPI ELFHeader64  :public ELFHeader  {
public:
    unsigned long long m_entry;
    unsigned long long m_phoff;
    unsigned long long m_shoff;
};

class foxintangoAPI ELFSegment64 :public ELFSegment {
public:
    unsigned long long	m_offset;
    unsigned long long	m_vaddr;
    unsigned long long	m_paddr;
    unsigned long long	m_filesz;
    unsigned long long	m_memsz;
    unsigned long long	m_align;
};
class foxintangoAPI ELFSection64 :public ELFSection {
public:
    unsigned long long	m_flags;
    unsigned long long	m_addr;
    unsigned long long	m_offset;
    unsigned long long	m_size;
    unsigned long long	m_addralign;
    unsigned long long	m_entsize;
};

class foxintangoAPI ELFFile{
public:
    ELFFile();
    ELFFile(const char* path);
    ~ELFFile();
public:
    unsigned int shstrndx;//https://man7.org/linux/man-pages/man5/elf.5.html e_shstrndx
    ELFIdent ident;
    ELFHeader* header;
    Array<ELFSegment*> segments;
    Array<ELFSection*> sections;
    Array<ELFStringTable*> stringTables;
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

     /** 
      * fix endian
      */
     int fix();
};
namespaceEnd
EXTERN_C_END
#endif // !_LIB_ELF_FILE_H_
