#ifndef __LIBPRINT_H
#define __LIBPRINT_H

#include <iostream>
#include <string>

#ifdef _DEBUG
#define MSG_PRINT(a) CPrinter::printMessage(a,4)
#define DBG_PRINT(a) CPrinter::printMessage(a,3)
#define WRN_PRINT(a) CPrinter::printMessage(a,2)
#define ERR_PRINT(a) CPrinter::printMessage(a,1)
#else 
#define MSG_PRINT(a)
#define DBG_PRINT(a)
#define WRN_PRINT(a)
#define ERR_PRINT(a)
#endif

// To use this printer, first call setDebugLevel([0-4]), then use above macros.
class CPrinter
{
public:
	CPrinter();
	static void setDebugLevel(unsigned lvl);			// 0 - none, 1 - error, 2 - warnings, 3 - debug, 4 - info messages
	static unsigned getDebugLevel();
	static int printMessage(const std::string& msg, unsigned lvl);	// returns -1 when current dbg_lvl is higher than lvl, -2 if lvl>3
protected:
	static unsigned dbg_lvl;
	static void print(const std::string& msg);
};


#endif
