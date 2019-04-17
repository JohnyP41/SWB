#include "dbgPrint.h"

#define MAX_DBG_LVL 4

using namespace std;
const char* const prefixes[] = {"","OUT_ERR ","OUT_WRN ","OUT_DBG ","OUT_MSG "};

unsigned CPrinter::dbg_lvl(0);

CPrinter::CPrinter()
{
}

int CPrinter::printMessage(const string& msg, unsigned lvl)
{
	if(lvl > 4)
	{
		return -2;
	}
	if(lvl <= dbg_lvl)
	{
		string localCpy = msg;
		localCpy.insert(0,prefixes[lvl]);
		print(localCpy);
		return 0;
	}
	else
	{
		return -1;
	}
}
void CPrinter::print(const std::string& msg)
{
	cout<<msg<<endl;
}

void CPrinter::setDebugLevel(unsigned lvl)
{
	dbg_lvl = ((lvl <= MAX_DBG_LVL) ? lvl : MAX_DBG_LVL);
}

unsigned CPrinter::getDebugLevel()
{
	return dbg_lvl;
}
