CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
AR=arm-none-eabi-ar
LD=arm-none-eabi-ld

OUT_DIR := ./out

#CCFLAGS = -c -fPIC -Wall -fvisibility=hidden
#PPFLAGS = -c -fPIC -Wall -fvisibility=hidden -std=c++11
CCFLAGS = -c -fPIC -Wall -fvisibility=hidden
PPFLAGS = -c -fPIC -Wall -fvisibility=hidden -std=c++11
LDFLAGS = 

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
	@echo ${LIB_A_OBJECTS_PP}
	$(CC) -fPIC -shared -lstdc++ -o $@ $^ ${LDFLAGS} -Wl,-Map=${OUT_DIR}/${LIB_A_NAME}.${LIB_MAP_EXT}

$(LIB_A_OBJECTS_CC):%.o:%.c
	arm-none-eabi-gcc -c -fPIC -Wall -fvisibility=hidden -std=c++11 $< -o $@ # $(CC) ${CCFLAGS} $< -o $@
$(LIB_A_OBJECTS_PP):%.o:%.cpp
	arm-none-eabi-gcc -c -fPIC -Wall -fvisibility=hidden -std=c++11 $< -o $@ # $(CC) ${PPFLAGS} $< -o $@

${OUT_DIR}/${LIB_B_NAME}.${LIB_NAME_EXT} ${OUT_DIR}/${LIB_B_NAME}.${LIB_MAP_EXT}:$(LIB_B_OBJECTS_PP) $(LIB_B_OBJECTS_CC)
	$(CC) -fPIC -shared -lstdc++ -o $@ $^ ${LDFLAGS} -Wl,-Map=${OUT_DIR}/${LIB_B_NAME}.${LIB_MAP_EXT}

$(LIB_B_OBJECTS_CC):%.o:%.c
	$(CC) ${CCFLAGS} $< -o $@
$(LIB_B_OBJECTS_PP):%.o:%.cpp
	$(CC) ${PPFLAGS} $< -o $@

${OUT_DIR}/${APP_OUT_NAME}.${APP_LST_EXT}:
	arm-none-eabi-objdump -h -t -S -C ${OUT_DIR}/${APP_OUT_NAME}.${APP_OUT_EXT} > ${OUT_DIR}/${APP_OUT_NAME}.${APP_LST_EXT}
${OUT_DIR}/${LIB_A_NAME}.${LIB_LST_EXT}:
	arm-none-eabi-objdump -h -t -S -C ${OUT_DIR}/${LIB_A_NAME}.${LIB_NAME_EXT}  > ${OUT_DIR}/${LIB_A_NAME}.${LIB_LST_EXT}
${OUT_DIR}/${LIB_B_NAME}.${LIB_LST_EXT}:
	arm-none-eabi-objdump -h -t -S -C ${OUT_DIR}/${LIB_B_NAME}.${LIB_NAME_EXT}  > ${OUT_DIR}/${LIB_B_NAME}.${LIB_LST_EXT}
clean   :
	-rm -rf ./out/*
	-rm -f $(APP_OBJECTS_CC)
	-rm -f $(APP_OBJECTS_PP)
	-rm -f $(LIB_A_OBJECTS_CC)
	-rm -f $(LIB_A_OBJECTS_PP)
	-rm -f $(LIB_B_OBJECTS_CC)
	-rm -f $(LIB_B_OBJECTS_PP)