int a;

int add(){
    a = 0;
}

int sub(){
    a = 1;
}
/*
 arm-none-eabi-g++ -c -fPIC -Wall -fvisibility=hidden -std=c++11 -o liba/share.o liba/share.cpp
 arm-none-eabi-g++ -fPIC -shared -lstdc++ -o out/liba.so lib/liba.o -Wl,-Map=./out/liba.map
 arm-none-eabi-objdump -h -S ./out/liba.so  > ./out/liba.lst
/*