int a;
int b;
int c;
int d;

int add(){
    a = 0;
    return a;
}

int sub(){
    a = 1;
    return a;
}

int div() {
    a = 2;
    return a;
}
/*
 arm-none-eabi-g++ -c -fPIC -Wall -fvisibility=hidden -std=c++11 -o liba/share.o liba/share.cpp
 arm-none-eabi-g++ -fPIC -shared -lstdc++ -o out/liba.so lib/liba.o -Wl,-Map=./out/liba.map
 arm-none-eabi-objdump -h -S ./out/liba.so  > ./out/liba.lst
*/