#include <stdlib.h>
#include <stdio.h>

#define ARRAY_SIZE 100000
int main(int argc, char* argv[])
{
        int i, test=5;
        int* buf = new int[100000];
        for (i=0; i< ARRAY_SIZE; i++){
                buf[i] = i;
        }
        int result = 0;
        delete []buf;
        
        printf("result: %d\n", result);
        delete[] buf;
        printf("test %d\n", test);
        return 0;
}

