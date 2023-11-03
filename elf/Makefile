CC=arm-none-eabi-g++
AS=arm-none-eabi-as
AR=arm-none-eabi-ar
LD=arm-none-eabi-ld

OUT_DIR := ./out

CCFLAGS = -c -fPIC -Wall -fvisibility=hidden
PPFLAGS = -c -fPIC -Wall -fvisibility=hidden -std=c++11
LDFLAGS = -fPIC -shared 

APP_OUT_NAME = app
APP_OUT_EXT  = elf
APP_MAP_EXT  = map
APP_SRC_DIR  =./app
APP_SOURCES_CC  += $(foreach dir,$(APP_SRC_DIR),$(wildcard $(dir)/*.c))
APP_OBJECTS_CC  += $(patsubst %.cpp,%.o,$(TARGET_SOURCES_PP))
APP_SOURCES_PP  += $(foreach dir,$(APP_SRC_DIR),$(wildcard $(dir)/*.cpp))
APP_OBJECTS_PP  += $(patsubst %.cpp,%.o,$(TARGET_SOURCES_PP))

LIB_A_SRC_DIR=./liba
LIB_B_SRC_DIR=./libb

TARGETS = app liba libb lst
ALL : ${OUT_DIR}/${APP_OUT_NAME}.${APP_OUT_EXT}
	
${OUT_DIR}/${APP_OUT_NAME}.${APP_OUT_EXT} ${OUT_DIR}/${APP_OUT_NAME}.${APP_MAP_EXT}:$(APP_OBJECTS_PP) $(APP_OBJECTS_CC)
	$(CC) -o $@ $^ ${LDFLAGS} -Wl,-Map=${OUT_DIR}/${APP_OUT_NAME}.${APP_MAP_EXT}

$(APP_OBJECTS_CC):%.o:%.c
	$(CC) ${CCFLAGS} $< -o $@
$(APP_OBJECTS_PP):%.o:%.cpp
	$(CC) ${PPFLAGS} $< -o $@