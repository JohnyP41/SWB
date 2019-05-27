#include <iostream>
#include <unistd.h>

int main() {

    unsigned int i = 0;
    while(true) {
	std::cout << ++i << std::endl;
	sleep(1);
    }
    return 0;
}
