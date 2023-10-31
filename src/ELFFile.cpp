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
        fclose(file);
        return 1;
    }
    return 0;
}

