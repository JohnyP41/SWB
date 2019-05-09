#include "../avg.h"


float avg(int array[], int w)
{
	int m=0, i;
	//int w = (sizeof(array)/sizeof(*array));
	for(i=0; i < w ; i++) {
		m += array[i];
	}
	//for (int i = 0 ; i < sizeof(array)/sizeof(array[0]); i++ ) {
	//	if (array[i]>m)
	//		m = array[i];
	//}
	return ((float)m/i);
}
