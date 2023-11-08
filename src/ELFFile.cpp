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
    FILE* file = fopen(path,"r");
    char elf_magic[4];
    char elf_bitwide;
    char elf_edian;
    char elf_version;
    Endian edian;
    // 参考 https://www.cnblogs.com/jiqingwu/p/elf_explore_2.html
    if(file){
        fread(&elf_magic,1,4,file);//
        fread(&elf_bitwide,1,1,file);//5
        fread(&elf_edian, 1, 1, file);//6
        fread(&elf_version,1,1,file);

        printf("elf_magic:   %c%c%c%c\n", elf_magic[0], elf_magic[1], elf_magic[2], elf_magic[3]);
        printf("elf_bitwide: %d\n", (int)elf_bitwide);
        printf("elf_edian:   %d\n", (int)elf_edian);
        printf("elf_version: %d\n", (int)elf_version);

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

        fseek(file, symtab_off, SEEK_SET);
        fread(strtab, 1, shstrtab_size, file);

        fseek(file, symtab_off, SEEK_SET);
        fread(shstrtab, 1, shstrtab_size, file);

        char** strs = new char*[128];
        size_t str_count = str_split(strtab,strtab_size,strs,128);

        char** shstrs = new char* [128];
        size_t shstr_count = str_split(shstrtab, shstrtab_size, shstrs, 128);

        for(int i = 0;i < str_count;i ++){
            printf("str %d : %s str_size: %u\n",i,strs[i],string_length<char>(strs[i]));
        }

        for (int i = 0; i < shstr_count; i++) {
            printf("shstr %d : %sstr_size: %u\n", i, shstrs[i], string_length<char>(shstrs[i]));
        }

        fclose(file);
        return 1;
    }
    return 0;
}

