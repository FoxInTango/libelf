int a = 32;
char c = 'f';
void* p = (void*)0x10838;
int add(){
    a = 0;
    return a;
}

/*

int sub(){
    a = b * a;
    return d;
}

int div() {
    a = 2;
    return 0;
}
*/
/*
 arm-none-eabi-g++ -c -fPIC -O0 -g3 -Wall -fvisibility=hidden -std=c++11 -o liba/share.o liba/share.cpp
 arm-none-eabi-g++ -fPIC -shared -lstdc++ -o out/liba.so  liba/share.o -Wl,-Map=./out/liba.map
 arm-none-eabi-objdump -h -S ./out/liba.so  > ./out/liba.lst
*/