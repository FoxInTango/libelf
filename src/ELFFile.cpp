#include "ELFFile.h"
#include "elf.h"
using namespace foxintango;
#include <stdio.h>

/**
 * Linux Ӧ�ò�
 * Linux �ں˲�
 * MCU 
 */

#if defined(STM32F101x6) || defined(STM32F101xB) || defined(STM32F101xE) || defined(STM32F101xG) || \
    defined(STM32F102x6) || defined(STM32F102xB) || \
    defined(STM32F103x6) || defined(STM32F103xB) || defined(STM32F103xE) || defined(STM32F103xG) || \
    defined(STM32F105xC) || defined(STM32F107xC)
#define APOLLO_IN_KERNEL

/**
 * �˽�STM32 stdio��ʹ�÷�ʽ 
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
    // �ο� https://www.cnblogs.com/jiqingwu/p/elf_explore_2.html

    /* e_type
     
     ET_NONE, 0, No file type
     ET_REL, 1, Relocatable file�����ض�λ�ļ���ͨ�����ļ�����.o��β��Ŀ���ļ���
     ET_EXEC, 2, Executable file ����ִ���ļ���
     ET_DYN, 3, Shared object file ����̬���ļ�������gcc������Ķ���������Ҳ�����������ͣ������𣿣�
     ET_CORE, 4, Core file ��core�ļ�����core dump���ɵİɣ���
     ET_NUM, 5����ʾ�Ѿ�������5���ļ�����
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
    uint16_t e_type;        //  2�ֽڣ�������ELF�ļ������͡�
    uint16_t e_machine;     //  2�ֽ�,�������ļ�����ļܹ�����ȡֵ���£���Ϊ�ĵ����ϣ������и���ȡֵ���μ�/usr/include/elf.h�е�EM_��ͷ�ĺ궨�壩��
    uint32_t e_version;     //  2�ֽ�,������ELF�ļ��İ汾�ţ��Ϸ�ȡֵ���£�
    uint32_t e_entry;       // ��32λ4�ֽڣ�64λ8�ֽڣ���ִ����ڵ㣬����ļ�û����ڵ㣬����򱣳�0��
    uint64_t e_entry_64;
    uint32_t e_phoff;       //  (32λ4�ֽڣ�64λ8�ֽڣ���program header table��offset������ļ�û��PH�����ֵ��0��
    uint64_t e_phoff_64;
    uint32_t e_shoff;       //  (32λ4�ֽڣ�64λ8�ֽڣ��� section header table ��offset������ļ�û��SH�����ֵ��0��
    uint64_t e_shoff_64;
    uint32_t e_flags;       //  4�ֽڣ��ض��ڴ������ı�־��32λ��64λIntel�ܹ���û�ж����־�����eflags��ֵ��0��
    uint16_t e_ehsize;      //  2�ֽڣ�ELF header�Ĵ�С��32λELF��52�ֽڣ�64λ��64�ֽڡ�
    uint16_t e_phentsize;   //  2�ֽڡ�program header table��ÿ����ڵĴ�С��
    uint16_t e_phnum;       //  2�ֽڡ�����ļ�û��program header table, e_phnum��ֵΪ0��e_phentsize����e_phnum�͵õ�������program header table�Ĵ�С��
    uint16_t e_shentsize;   //  2�ֽڣ�section header table��entry�Ĵ�С����ÿ��section headerռ�����ֽڡ�
    uint16_t e_shnum;       //  2�ֽڣ�section header table��header����Ŀ������ļ�û��section header table, e_shnum��ֵΪ0��e_shentsize����e_shnum���͵õ�������section header table�Ĵ�С��
    uint16_t e_shstrndx;    //  2�ֽڡ�section header string table index.������section header table��section name string table�����û��section name string table, e_shstrndx��ֵ��SHN_UNDEF
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

        // �����ֽ���

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
        printf("elf_magic:   %c%c%c%c\n", e_i_magic[0], e_i_magic[1], e_i_magic[2], e_i_magic[3]);

        printf("elf_bitwide: %d\n", (int)e_i_bitwide);
        printf("elf_edian:      %d\n", (int)e_i_edian);
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

