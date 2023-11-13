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
#include <stdlib.h>
#include <stdio.h>

/**
 *    0111011101111111011110
 */
size_t str_split(char* buffer,const size_t& length,char** strs,const size_t& strs_size){
    size_t index = 0;
    size_t count = 0;

    for(index; index < length; index++){
        if(buffer[index] != '\0') break;
    }

    if(index == 0){
        strs[0] = &buffer[index];
        count ++;

        for (index; index < length; index++) {
            if (buffer[index] != '\0') break;
        }
    }

    if(index >= length) return count;

    while(index < length && count < strs_size){
        if(buffer[index] != '\0' && buffer[index - 1] == '\0'){
            strs[count] = &buffer[index];
            count ++;
        }

        index ++;
    }

return count;
}

typedef struct {
    uint32_t   p_type;
    uint32_t   p_flags;
    Elf64_Off  p_offset;
    Elf64_Addr p_vaddr;
    Elf64_Addr p_paddr;
    uint64_t   p_filesz;
    uint64_t   p_memsz;
    uint64_t   p_align;
} Elf64_Phdr_t;

int ELFFile::open(const char* path){
    unsigned char endian = (unsigned char)(CurrentEndian());

    FILE* file = fopen(path,"r");
    // 参考 https://www.cnblogs.com/jiqingwu/p/elf_explore_2.html
    //      https://github.com/ARM-software/abi-aa/blob/main/aaelf32/aaelf32.rst

    // 静态库 格式 ： https://zhuanlan.zhihu.com/p/24885933

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
    unsigned char	e_ident[EI_NIDENT];
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
                            // e_shstrndx : 最后一个e_shstrndx表示的是section table中的第e_shstrndx项元素，保存了所有section table名称的字符串信息。https://zhuanlan.zhihu.com/p/254882216
    if(file){
        /*
        fread(&e_i_magic,  1, 4, file);//
        fread(&e_i_bitwide,1, 1, file);//5
        fread(&e_i_endian,  1, 1, file);//6
        fread(&e_i_version,1, 1, file);
        */
        printf("ELF File %s loaded.\n",path);

        char* e_entry_string = 0;
        char* e_phoff_string = 0;
        char* e_shoff_string = 0;
        fread(&e_ident, 1, EI_NIDENT, file);
        printf("Platform Endian : %d ELFEndian: %d\n", endian, (int)e_ident[5]);
        fread(&e_type,    1, 2, file);
        fread(&e_machine, 1, 2, file);
        fread(&e_version, 1, 4, file);
        if((unsigned char)e_ident[4] == 1){
            fread(&e_entry, 1, 4, file);
            fread(&e_phoff, 1, 4, file);
            fread(&e_shoff, 1, 4, file);
            /*
            if (endian != e_ident[5]) {
            e_entry = endianSwap32u(e_entry);
            e_phoff = endianSwap32u(e_phoff);
            e_shoff = endianSwap32u(e_shoff);
            }*/
            printf("e_entry: %u \n", e_entry);
            printf("e_phoff: %u \n", e_phoff);
            printf("e_shoff: %u \n", e_shoff);
        }else { 
            fread(&e_entry_64, 1, 8, file);
            fread(&e_phoff_64, 1, 8, file);
            fread(&e_shoff_64, 1, 8, file);
            /*
            if (endian != e_ident[5]) {
            e_entry_64 = endianSwap64u(e_entry_64);
            e_phoff_64 = endianSwap64u(e_phoff_64);
            e_shoff_64 = endianSwap64u(e_shoff_64);
            }*/
            printf("e_entry_64: %llu \n", e_entry_64);
            printf("e_phoff_64: %llu \n", e_phoff_64);
            printf("e_shoff_64: %llu \n", e_shoff_64);
        }
        fread(&e_flags, 1, 4, file);
        fread(&e_ehsize, 1, 2, file);
        fread(&e_phentsize, 1, 2, file);
        fread(&e_phnum, 1, 2, file);
        fread(&e_shentsize, 1, 2, file);
        fread(&e_shnum,  1, 2, file);
        fread(&e_shstrndx, 1, 2, file);

        // 处理字节序
        /*
        if(endian != e_ident[5]){
            e_type      = endianSwap16u(e_type);
            e_machine   = endianSwap16u(e_machine);
            e_version   = endianSwap32u(e_version);
            e_flags     = endianSwap32u(e_flags);
            e_ehsize    = endianSwap16u(e_ehsize);
            e_phentsize = endianSwap16u(e_phentsize);
            e_phnum     = endianSwap16u(e_phnum);
            e_shentsize = endianSwap16u(e_shentsize);
            e_shnum     = endianSwap16u(e_shnum);
            e_shstrndx  = endianSwap16u(e_shstrndx);
        }*/
        printf("elf_magic:     %c%c%c%c\n", e_ident[0], e_ident[1], e_ident[2], e_ident[3]);
        printf("elf_bitwide:   %d\n", (int)e_ident[4]);
        printf("elf_edian:     %d\n", (int)e_ident[5]);
        printf("elf_version:   %d\n", (int)e_ident[6]);
        printf("elf_type:      %d\n", e_type);
        printf("elf_version:   %d\n", e_version);
        printf("elf_flags:     %d\n", e_flags);
        printf("elf_ehsize:    %d\n", e_ehsize);
        printf("elf_phentsize: %d\n", e_phentsize);
        printf("elf_phnum:     %d\n", e_phnum);
        printf("elf_shentsize: %d\n", e_shentsize);
        printf("elf_shnum:     %d\n", e_shnum);
        printf("elf_shstrndx:  %d\n", e_shstrndx);

        /*
        size_t symtab_off = 0x000a0c;
        size_t strtab_off = 0x000d0c;
        size_t shstrtab_off = 0x0010d4;

        size_t symtab_size = 0x000300;
        size_t strtab_size = 0x000100;
        size_t shstrtab_size = 0x0000d0;

        char* symtab = new char[symtab_size + 1];
        char* strtab = new char[strtab_size + 1];
        char* shstrtab = new char[shstrtab_size + 1];

        fseek(file,symtab_off, SEEK_SET);
        fread(symtab,1,symtab_size,file);

        fseek(file, strtab_off, SEEK_SET);
        fread(strtab, 1, strtab_size, file);

        fseek(file, shstrtab_off, SEEK_SET);
        fread(shstrtab, 1, shstrtab_size, file);

        char** strs = new char*[128];
        size_t str_count = str_split(strtab,strtab_size,strs,128);

        char** shstrs = new char* [128];
        size_t shstr_count = str_split(shstrtab, shstrtab_size, shstrs, 128);
        
        for(int i = 0;i < str_count;i ++){
            printf("str   %d : size: %u -- %s \n",i, string_length<char>(strs[i]),strs[i]);
        }
        
        for (int i = 0; i < shstr_count; i++) {
            printf("shstr %d : size: %u -- %s \n", i, string_length<char>(shstrs[i]), shstrs[i]);
        }
        */

        /*
        for(int i = 0;i < strtab_size;i ++){
            if(strtab[i] == 0){
                printf(" | ");
            }else{
                printf("%c",strtab[i]);
            }
        }

        for (int i = 0; i < shstrtab_size; i++) {
            if (shstrtab[i] == 0) {
                printf(" | ");
            }
            else {
                printf("%c", shstrtab[i]);
            }
        }
        */
        // program headers https://man7.org/linux/man-pages/man5/elf.5.html

        if(e_phnum){
            // 32位
            fseek(file,e_phoff,0);

            if(e_ident[4] == 1){
                for(int i = 0;i < e_phnum;i ++){
                    Elf32_Phdr ph;
                    fread(&ph,1,sizeof(Elf32_Phdr),file);
                    printf("Program Header %d :\n",i);
                    char* p_type_s_null    = "PT_NULL";
                    char* p_type_s_load    = "PT_LOAD";
                    char* p_type_s_dynamic = "PT_DYNAMIC";
                    char* p_type_s_interp  = "PT_INTERP";
                    char* p_type_s_note    = "PT_NOTE";
                    char* p_type_s_shlib   = "PT_SHLIB";
                    char* p_type_s_phdr    = "PT_PHDR";
                    char* p_type_s_stack   = "PT_GNU_STACK";
                    char* p_type_s_proc    = "PT_PROC";//PT_LOPROC, PT_HIPROC

                    switch(ph.p_type){
                    case PT_NULL:      {printf("    Segment Type: %s  ", p_type_s_null);    }break;
                    case PT_LOAD:      {printf("    Segment Type: %s  ", p_type_s_load);    }break;
                    case PT_DYNAMIC:   {printf("    Segment Type: %s  ", p_type_s_dynamic); }break;
                    case PT_INTERP:    {printf("    Segment Type: %s  ", p_type_s_interp);  }break;
                    case PT_NOTE:      {printf("    Segment Type: %s  ", p_type_s_note);    }break;
                    case PT_SHLIB:     {printf("    Segment Type: %s  ", p_type_s_shlib);   }break;
                    case PT_PHDR:      {printf("    Segment Type: %s  ", p_type_s_phdr);    }break;
                    case PT_GNU_STACK: {printf("    Segment Type: %s  ", p_type_s_stack);   }break;
                    default:{
                        if(ph.p_type >= PT_LOPROC && ph.p_type <= PT_HIPROC){
                            printf("    Segment Type: %s  ", p_type_s_proc);
                        }
                    }break;
                    }

                    printf("\n");
                }

                
            } else {
            // 64位
                for (int i = 0; i < e_phnum; i++) {
                    Elf64_Phdr_t ph;
                    fread(&ph,sizeof(Elf64_Phdr_t),1, file);
                    printf("Program Header %d :\n", i);
                    char* p_type_s_null    = "PT_NULL";
                    char* p_type_s_load    = "PT_LOAD";
                    char* p_type_s_dynamic = "PT_DYNAMIC";
                    char* p_type_s_interp  = "PT_INTERP";
                    char* p_type_s_note    = "PT_NOTE";
                    char* p_type_s_shlib   = "PT_SHLIB";
                    char* p_type_s_phdr    = "PT_PHDR";
                    char* p_type_s_stack   = "PT_GNU_STACK";
                    char* p_type_s_proc    = "PT_PROC";//PT_LOPROC, PT_HIPROC

                    switch (ph.p_type) {
                    case PT_NULL:      {printf("    Segment Type: %s  ", p_type_s_null);    }break;
                    case PT_LOAD:      {printf("    Segment Type: %s  ", p_type_s_load);    }break;
                    case PT_DYNAMIC:   {printf("    Segment Type: %s  ", p_type_s_dynamic); }break;
                    case PT_INTERP:    {printf("    Segment Type: %s  ", p_type_s_interp);  }break;
                    case PT_NOTE:      {printf("    Segment Type: %s  ", p_type_s_note);    }break;
                    case PT_SHLIB:     {printf("    Segment Type: %s  ", p_type_s_shlib);   }break;
                    case PT_PHDR:      {printf("    Segment Type: %s  ", p_type_s_phdr);    }break;
                    case PT_GNU_STACK: {printf("    Segment Type: %s  ", p_type_s_stack);   }break;
                    default: {
                        if (ph.p_type >= PT_LOPROC && ph.p_type <= PT_HIPROC) {
                            printf("    Segment Type: %s  ", p_type_s_proc);
                        } else{
                            printf("    Segment Type Value %u : %",ph.p_type);
                        }
                    }break;
                    }

                    printf("\n");
                }
            }
        }
        // section headers https://man7.org/linux/man-pages/man5/elf.5.html
        if (e_shnum) {
            // 32位
            fseek(file, e_shoff, 0);
            if (e_ident[4] == 1) {
                for (int i = 0; i < e_shnum; i++) {
                    Elf32_Shdr sh;
                    fread(&sh, sizeof(Elf32_Shdr), 1, file);
                    printf("Section Header %d :\n", i);
                } else {
                    Elf64_Shdr sh;
                    fread(&sh, sizeof(Elf64_Shdr), 1, file);
                    printf("Section Header %d :\n", i);
                }
            }

        }
        fclose(file);
        return 1;
    }
    return 0;
}

