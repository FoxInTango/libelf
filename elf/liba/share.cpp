int  a = 32;
int  b = 64;
char c = 'f';
char d = 'g';
void* p = (void*)0x10838;
int add(){
    a = 0;
    /*
    b = 32;
    c = 'a';
    d = 'd';
    p = (void*)0x10839;
    */
    return a;
}

void assign(){
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

  // 计算 got 地址 存入 r3 ：740 + 8 + 0x00010198
  // got 偏移量 ： 0x00000030 + 8
  // 加载 GOT 项 ： 740 + 8 + 0x00010198 + 0x00000030 + 8 =

  // https://www.zhihu.com/question/472094994 <<linker and loader>>
*/