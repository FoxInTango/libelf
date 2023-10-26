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

int ELF::open(const char* path){
    FILE* file = fopen(path,"r");

    if(file){
        fclose(file);
        return 1;
    }
    return 0;
}

