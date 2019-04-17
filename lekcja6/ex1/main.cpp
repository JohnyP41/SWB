#include "./main.h"
#include "./dbgPrint.h"

using namespace std;

int main()
{
    CPrinter C;
    C.setDebugLevel(3);
    C.printMessage("testtt", 3);
    printMessage("Hello makefiles");
    return 0;
}
