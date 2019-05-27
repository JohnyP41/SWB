#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <cstdio>

#define LOG(msg, args...) fprintf(stderr, msg"\n", ##args)

#endif /* _DEBUG_H_ */
