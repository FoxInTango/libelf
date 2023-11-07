ifeq ($(OS),Windows_NT)
CC=arm-none-eabi-gcc
PP=arm-none-eabi-g++
AS=arm-none-eabi-as
AR=arm-none-eabi-ar
LD=arm-none-eabi-ld
OD=arm-none-eabi-objdump
RE=arm-none-eabi-readelf
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
	    CC=gcc
        PP=g++
        AS=as
        AR=ar
        LD=ld
        OD=objdump
		RE=readelf
    endif
    ifeq ($(UNAME_S),Darwin)
    endif
endif
# 使用strip, eu-strip, objcopy等剥离与导回符号表及调试信息
# https://blog.csdn.net/nirendao/article/details/104107608
# https://zhuanlan.zhihu.com/p/609045881
ASFLAGS = 
CCFLAGS = -O0 -g -Wall -c -fmessage-length=0 -fPIC #-MMD -MP # -c -fPIC -O0 -Wall -fvisibility=hidden # -g3
PPFLAGS = -O0 -g -Wall -c -fmessage-length=0 -fPIC #-MMD -MP # -c -fPIC -O0 -Wall -fvisibility=hidden -std=c++11 # -g3
LDFLAGS = -fPIC -shared # -lstdc++
ODFLAGS = -h -d -w -s -S -t -T -r -R -C
REFLAGS = -a

OUT_DIR := ./out

# app
APP_OUT_NAME = app
APP_OUT_EXT  = elf
APP_MAP_EXT  = map
APP_LST_EXT  = lst
APP_SRC_DIR  =./app
ifeq ($(OS),Windows_NT)
CC=arm-none-eabi-gcc
PP=arm-none-eabi-g++
AS=arm-none-eabi-as
AR=arm-none-eabi-ar
LD=arm-none-eabi-ld
OD=arm-none-eabi-objdump
APP_SOURCES_CC  += ${APP_SRC_DIR}/syscalls.c
APP_SOURCES_CC  += ${APP_SRC_DIR}/sysmem.c
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
	    CC=gcc
        PP=g++
        AS=as
        AR=ar
        LD=ld
        OD=objdump
    endif
    ifeq ($(UNAME_S),Darwin)
    endif
endif
APP_OBJECTS_CC  += $(patsubst %.c,%.o,$(APP_SOURCES_CC))
APP_SOURCES_PP  += ${APP_SRC_DIR}/main.cpp
APP_OBJECTS_PP  += $(patsubst %.cpp,%.o,$(APP_SOURCES_PP))
APP_OBJECTS_LST += $(patsubst %.c,%.o,$(APP_OBJECTS_CC))
APP_OBJECTS_LST += $(patsubst %.c,%.o,$(APP_OBJECTS_PP))

# lib 
LIB_NAME_EXT = so
LIB_MAP_EXT  = map
LIB_LST_EXT  = lst

# liba 
LIB_A_NAME        = liba
LIB_A_SRC_DIR     =./liba
LIB_A_SOURCES_CC  += 
LIB_A_OBJECTS_CC  += $(patsubst %.c,%.o,$(LIB_A_SOURCES_CC))
LIB_A_SOURCES_PP  += ${LIB_A_SRC_DIR}/share.cpp
LIB_A_OBJECTS_PP  += $(patsubst %.cpp,%.o,$(LIB_A_SOURCES_PP))

# libb 
LIB_B_NAME        = libb
LIB_B_SRC_DIR     =./libb
LIB_B_SOURCES_CC  += 
LIB_B_OBJECTS_CC  += $(patsubst %.c,%.o,$(LIB_B_SOURCES_CC))
LIB_B_SOURCES_PP  += ${LIB_B_SRC_DIR}/share.cpp
LIB_B_OBJECTS_PP  += $(patsubst %.cpp,%.o,$(LIB_B_SOURCES_PP))

ALL : ${OUT_DIR}/${APP_OUT_NAME}.${APP_OUT_EXT} ${OUT_DIR}/${APP_OUT_NAME}.${APP_LST_EXT} ${APP_OBJECTS_LST}\
      ${OUT_DIR}/${LIB_A_NAME}.${LIB_NAME_EXT} ${OUT_DIR}/${LIB_A_NAME}.${LIB_LST_EXT}    \
      ${OUT_DIR}/${LIB_B_NAME}.${LIB_NAME_EXT} ${OUT_DIR}/${LIB_B_NAME}.${LIB_LST_EXT}
	
${OUT_DIR}/${APP_OUT_NAME}.${APP_OUT_EXT} ${OUT_DIR}/${APP_OUT_NAME}.${APP_MAP_EXT}:$(APP_OBJECTS_PP) $(APP_OBJECTS_CC)
	$(PP) -o $@ $^ ${LDFLAGS} -Wl,-Map=${OUT_DIR}/${APP_OUT_NAME}.${APP_MAP_EXT}

$(APP_OBJECTS_CC):%.o:%.c
	$(CC) ${CCFLAGS} $< -o $@
$(APP_OBJECTS_PP):%.o:%.cpp
	$(PP) ${PPFLAGS} $< -o $@
$(APP_OBJECTS_LST):%.lst %.o
	$(OD) ${ODFLAGS} $< -o $@

${OUT_DIR}/${LIB_A_NAME}.${LIB_NAME_EXT} ${OUT_DIR}/${LIB_A_NAME}.${LIB_MAP_EXT}:$(LIB_A_OBJECTS_PP) $(LIB_A_OBJECTS_CC)
	$(PP) ${LDFLAGS} -o $@ $^ -Wl,-Map=${OUT_DIR}/${LIB_A_NAME}.${LIB_MAP_EXT}

$(LIB_A_OBJECTS_CC):%.o:%.c
	$(CC) ${CCFLAGS}  -o $@ $<
$(LIB_A_OBJECTS_PP):%.o:%.cpp
	$(PP) ${PPFLAGS}  -o $@ $<


${OUT_DIR}/${LIB_B_NAME}.${LIB_NAME_EXT} ${OUT_DIR}/${LIB_B_NAME}.${LIB_MAP_EXT}:$(LIB_B_OBJECTS_PP) $(LIB_B_OBJECTS_CC)
	$(PP) ${LDFLAGS} -o $@ $^ -Wl,-Map=${OUT_DIR}/${LIB_B_NAME}.${LIB_MAP_EXT}

$(LIB_B_OBJECTS_CC):%.o:%.c
	$(CC) ${CCFLAGS} $< -o $@
$(LIB_B_OBJECTS_PP):%.o:%.cpp
	$(PP) ${PPFLAGS} $< -o $@

${OUT_DIR}/${APP_OUT_NAME}.${APP_LST_EXT}:
	$(OD) ${ODFLAGS} ${OUT_DIR}/${APP_OUT_NAME}.${APP_OUT_EXT} > ${OUT_DIR}/${APP_OUT_NAME}.${APP_LST_EXT} #-h -t -D -S -C 
${OUT_DIR}/${LIB_A_NAME}.${LIB_LST_EXT}:
	$(OD) ${ODFLAGS} ${OUT_DIR}/${LIB_A_NAME}.${LIB_NAME_EXT}  > ${OUT_DIR}/${LIB_A_NAME}.${LIB_LST_EXT}   # -h -d -s -t -S -C 
${OUT_DIR}/${LIB_B_NAME}.${LIB_LST_EXT}:
	$(OD) ${ODFLAGS} ${OUT_DIR}/${LIB_B_NAME}.${LIB_NAME_EXT}  > ${OUT_DIR}/${LIB_B_NAME}.${LIB_LST_EXT}   # -h -t -D -S -C 
clean   :
	-rm -rf ./out/*
	-rm -f $(APP_OBJECTS_CC)
	-rm -f $(APP_OBJECTS_PP)
	-rm -f $(LIB_A_OBJECTS_CC)
	-rm -f $(LIB_A_OBJECTS_PP)
	-rm -f $(LIB_B_OBJECTS_CC)
	-rm -f $(LIB_B_OBJECTS_PP)