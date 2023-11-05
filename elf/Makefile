CC=arm-none-eabi-gcc
PP=arm-none-eabi-g++
AS=arm-none-eabi-as
AR=arm-none-eabi-ar
LD=arm-none-eabi-ld
OD=arm-none-eabi-objdump

# arm-none-eabi-g++ -c -fPIC -O0 -g3 -Wall -fvisibility=default -std=c++11

ASFLAGS = 
CCFLAGS = -c -fPIC -O0 -g3 -Wall -fvisibility=hidden
PPFLAGS = -c -fPIC -O0 -g3 -Wall -fvisibility=hidden -std=c++11
LDFLAGS = -fPIC -shared -lstdc++ 
ODFLAGS = -h -d -s -t -S -C

OUT_DIR := ./out

# app
APP_OUT_NAME = app
APP_OUT_EXT  = elf
APP_MAP_EXT  = map
APP_LST_EXT  = lst
APP_SRC_DIR  =./app
APP_SOURCES_CC  += ${APP_SRC_DIR}/syscalls.c
APP_SOURCES_CC  += ${APP_SRC_DIR}/sysmem.c
APP_OBJECTS_CC  += $(patsubst %.c,%.o,$(APP_SOURCES_CC))
APP_SOURCES_PP  += ${APP_SRC_DIR}/main.cpp
APP_OBJECTS_PP  += $(patsubst %.cpp,%.o,$(APP_SOURCES_PP))

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

ALL : ${OUT_DIR}/${APP_OUT_NAME}.${APP_OUT_EXT} ${OUT_DIR}/${APP_OUT_NAME}.${APP_LST_EXT} \
      ${OUT_DIR}/${LIB_A_NAME}.${LIB_NAME_EXT} ${OUT_DIR}/${LIB_A_NAME}.${LIB_LST_EXT}    \
      ${OUT_DIR}/${LIB_B_NAME}.${LIB_NAME_EXT} ${OUT_DIR}/${LIB_B_NAME}.${LIB_LST_EXT}
	
${OUT_DIR}/${APP_OUT_NAME}.${APP_OUT_EXT} ${OUT_DIR}/${APP_OUT_NAME}.${APP_MAP_EXT}:$(APP_OBJECTS_PP) $(APP_OBJECTS_CC)
	$(CC) -o $@ $^ ${LDFLAGS} -Wl,-Map=${OUT_DIR}/${APP_OUT_NAME}.${APP_MAP_EXT}

$(APP_OBJECTS_CC):%.o:%.c
	$(CC) ${CCFLAGS} $< -o $@
$(APP_OBJECTS_PP):%.o:%.cpp
	$(CC) ${PPFLAGS} $< -o $@

${OUT_DIR}/${LIB_A_NAME}.${LIB_NAME_EXT} ${OUT_DIR}/${LIB_A_NAME}.${LIB_MAP_EXT}:$(LIB_A_OBJECTS_PP) $(LIB_A_OBJECTS_CC)
	$(PP) -o $@ $^ ${LDFLAGS} -Wl,-Map=${OUT_DIR}/${LIB_A_NAME}.${LIB_MAP_EXT} #$(CC) -o $@ $^ ${LDFLAGS} -fPIC -shared -lstdc++ -Wl,-Map=${OUT_DIR}/${LIB_B_NAME}.${LIB_MAP_EXT} 
$(LIB_A_OBJECTS_CC):%.o:%.c
	$(CC) $< -o $@ ${CCFLAGS}
$(LIB_A_OBJECTS_PP):%.o:%.cpp
	$(PP) $< -o $@ ${PPFLAGS} #$(PP) -c $< -o $@ -fPIC -O0 -g3 -Wall -fvisibility=default -std=c++11 # $(CC) ${PPFLAGS} $< -o $@

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