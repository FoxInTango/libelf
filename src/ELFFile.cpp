#include "ELFFile.h"
#include "elf.h"
using namespace foxintango;
#include <stdio.h>

/**
 * Linux 应用层
 * Linux 内核层
 * MCU 
 */

#if defined(STM32F101x6) || defined(STM32F101xB) || defined(STM32F101xE) || defined(STM32F101xG) || \
    defined(STM32F102x6) || defined(STM32F102xB) || \
    defined(STM32F103x6) || defined(STM32F103xB) || defined(STM32F103xE) || defined(STM32F103xG) || \
    defined(STM32F105xC) || defined(STM32F107xC)
#define APOLLO_IN_KERNEL

/**
 * 了解STM32 stdio的使用方式 
 */
#endif

#define APOLLO_IN_KERNEL

#if defined(APOLLO_IN_KERNEL)
#endif

ELFFile::ELFFile(){}
ELFFile::ELFFile(const char* path){
    open(path);
}

ELFFile::~ELFFile(){}

size_t str_split(char* buffer,const size_t& length,char** strs,const size_t& str_arr_size){
    size_t index  = 0;
    size_t offset = 0;
    size_t str_count = 0;
    while(index < length && str_count < str_arr_size){
        if(buffer[index] == 0){
            size_t size = index - offset;
            char* str = new char[size + 1];
            memclr(str,size + 1,0);
            string_copy(str,buffer + offset,size);
            strs[str_count] = str;
            str_count ++;
            offset = index + 1;
        }
        index ++;
    }

    return str_count;
}
int ELFFile::open(const char* path){
    Endian endian = Endian(CurrentEndian());

    FILE* file = fopen(path,"r");
    // 参考 https://www.cnblogs.com/jiqingwu/p/elf_explore_2.html

    /* e_type
     
     ET_NONE, 0, No file type
     ET_REL, 1, Relocatable file（可重定位文件，通常是文件名以.o结尾，目标文件）
     ET_EXEC, 2, Executable file （可执行文件）
     ET_DYN, 3, Shared object file （动态库文件，你用gcc编译出的二进制往往也属于这种类型，惊讶吗？）
     ET_CORE, 4, Core file （core文件，是core dump生成的吧？）
     ET_NUM, 5，表示已经定义了5种文件类型
     ET_LOPROC, 0xff00, Processor-specific
     ET_HIPROC, 0xffff, Processor-specific
     */

    /* e_machine
     EM_NONE, 0, No machine
     EM_M32, 1, AT&T WE 32100
     EM_SPARC, 2, SPARC
     EM_386, 3, Intel 80386
     EM_68K, 4, Motorola 68000
     EM_88K, 5, Motorola 88000
     EM_860, 7, Intel 80860
     EM_MIPS, 8, MIPS RS3000
     */
    char e_i_magic[4];
    char e_i_bitwide;
    char e_i_endian;
    char e_i_version;
    uint16_t e_type;        //  2字节，描述了ELF文件的类型。
    uint16_t e_machine;     //  2字节,描述了文件面向的架构，可取值如下（因为文档较老，现在有更多取值，参见/usr/include/elf.h中的EM_开头的宏定义）：
    uint32_t e_version;     //  2字节,描述了ELF文件的版本号，合法取值如下：
    uint32_t e_entry;       // （32位4字节，64位8字节），执行入口点，如果文件没有入口点，这个域保持0。
    uint64_t e_entry_64;
    uint32_t e_phoff;       //  (32位4字节，64位8字节），program header table的offset，如果文件没有PH，这个值是0。
    uint64_t e_phoff_64;
    uint32_t e_shoff;       //  (32位4字节，64位8字节）， section header table 的offset，如果文件没有SH，这个值是0。
    uint64_t e_shoff_64;
    uint32_t e_flags;       //  4字节，特定于处理器的标志，32位和64位Intel架构都没有定义标志，因此eflags的值是0。
    uint16_t e_ehsize;      //  2字节，ELF header的大小，32位ELF是52字节，64位是64字节。
    uint16_t e_phentsize;   //  2字节。program header table中每个入口的大小。
    uint16_t e_phnum;       //  2字节。如果文件没有program header table, e_phnum的值为0。e_phentsize乘以e_phnum就得到了整个program header table的大小。
    uint16_t e_shentsize;   //  2字节，section header table中entry的大小，即每个section header占多少字节。
    uint16_t e_shnum;       //  2字节，section header table中header的数目。如果文件没有section header table, e_shnum的值为0。e_shentsize乘以e_shnum，就得到了整个section header table的大小。
    uint16_t e_shstrndx;    //  2字节。section header string table index.包含了section header table中section name string table。如果没有section name string table, e_shstrndx的值是SHN_UNDEF
    if(file){
        fread(&e_i_magic,  1, 4, file);//
        fread(&e_i_bitwide,1, 1, file);//5
        fread(&e_i_endian,  1, 1, file);//6
        fread(&e_i_version,1, 1, file);

        fread(&e_type,    1, 2, file);
        fread(&e_machine, 1, 2, file);
        fread(&e_version, 1, 4, file);
        if(e_i_bitwide == 1){
            fread(&e_entry, 1, 4, file);
            fread(&e_phoff, 1, 4, file);
            fread(&e_shoff, 1, 4, file);

            e_entry = endianSwap32u(e_entry);
            e_phoff = endianSwap32u(e_phoff);
            e_shoff = endianSwap32u(e_shoff);
        }else { 
            fread(&e_entry_64, 1, 8, file);
            fread(&e_phoff_64, 1, 8, file);
            fread(&e_shoff_64, 1, 8, file);
            e_entry_64 = endianSwap64u(e_entry_64);
            e_phoff_64 = endianSwap64u(e_phoff_64);
            e_shoff_64 = endianSwap64u(e_shoff_64);
        }
        fread(&e_flags,  1, 4, file);
        fread(&e_ehsize, 1, 2, file);
        fread(&e_phentsize, 1, 2, file);
        fread(&e_phnum, 1, 2, file);
        fread(&e_shentsize, 1, 2, file);
        fread(&e_shnum,  1, 2, file);
        fread(&e_phentsize, 1, 2, file);

        // 处理字节序

        if(endian != e_i_endian){
            e_type      = endianSwap16u(e_type);
            e_machine   = endianSwap16u(e_machine);
            e_version   = endianSwap32u(e_version);
            e_flags     = endianSwap32u(e_flags);
            e_ehsize    = endianSwap16u(e_ehsize);
            e_phentsize = endianSwap16u(e_phentsize);
            e_phnum     = endianSwap16u(e_phnum);
            e_shentsize = endianSwap16u(e_shentsize);
            e_shnum     = endianSwap16u(e_shnum);
            e_phentsize = endianSwap16u(e_phentsize);
        }
        printf("elf_magic:     %c%c%c%c\n", e_i_magic[0], e_i_magic[1], e_i_magic[2], e_i_magic[3]);
        printf("elf_bitwide:   %d\n", (int)e_i_bitwide);
        printf("elf_edian:     %d\n", (int)e_i_endian);
        printf("elf_version:   %d\n", (int)e_i_version);
        printf("elf_type:      %d\n", e_type);
        printf("elf_version:   %d\n", e_version);
        printf("elf_flags:     %d\n", e_flags);
        printf("elf_ehsize:    %d\n", e_ehsize);
        printf("elf_phentsize: %d\n", e_phentsize);
        printf("elf_phnum:     %d\n", e_phnum);
        printf("elf_shentsize: %d\n", e_shentsize);
        printf("elf_shnum:     %d\n", e_shnum);
        printf("elf_phentsize: %d\n", e_phentsize);
        size_t symtab_off = 0x000a0c;
        size_t strtab_off = 0x000d0c;
        size_t shstrtab_off = 0x0010d4;

        size_t symtab_size = 0x000300;
        size_t strtab_size = 0x000100;
        size_t shstrtab_size = 0x0000d0;

        char* symtab = new char[symtab_size + 1];
        char* strtab = new char[strtab_size + 1];
        char* shstrtab = new char[shstrtab_size];

        fseek(file,symtab_off, SEEK_SET);
        fread(symtab,1,symtab_size,file);

        fseek(file, strtab_off, SEEK_SET);
        fread(strtab, 1, shstrtab_size, file);

        fseek(file, shstrtab_off, SEEK_SET);
        fread(shstrtab, 1, shstrtab_size, file);

        char** strs = new char*[128];
        size_t str_count = str_split(strtab,strtab_size,strs,128);

        char** shstrs = new char* [128];
        size_t shstr_count = str_split(shstrtab, shstrtab_size, shstrs, 128);

        for(int i = 0;i < str_count;i ++){
            printf("str %d : %s str_size: %u\n",i,strs[i],string_length<char>(strs[i]));
        }
        //*
        for (int i = 0; i < shstr_count; i++) {
            printf("shstr %d : %s str_size: %u\n", i, shstrs[i], string_length<char>(shstrs[i]));
        }
        /*
        for(int i = 0;i < strtab_size;i ++){
            if(strtab[i] == 0){
                printf("\n");
            }else{
                printf("%c",strtab[i]);
            }
        }

        for (int i = 0; i < shstrtab_size; i++) {
            if (shstrtab[i] == 0) {
                printf("\n");
            }
            else {
                printf("%c", shstrtab[i]);
            }
        }
        */
        fclose(file);
        return 1;
    }
    return 0;
}

