#include "main.h"
#include "restaurant.cpp"

#include <stdlib.h>
#include <crtdbg.h>

#define _CRTDBG_MAP_ALLOC

// Sử dụng macro để thay thế new bằng DBG_NEW để theo dõi memory allocation
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

int main(int argc, char* argv[]) {
    string fileName = "test.txt";
    simulate(fileName);

    int* o = new int[3];
    o[0] = 8;
    o[1] = 9;
    o[2] = 10;
    
// In báo cáo về memory leak vào Output window khi chương trình kết thúc
    _CrtDumpMemoryLeaks();

    return 0;
}
