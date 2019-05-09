#include "../min.h"


int min(int array[], int w)
{
	int m=array[0];
	//int w = (sizeof(array)/sizeof(*array));
	for(int i = 0 ; i < w ; i++) {
		if (array[i]<m)
			m = array[i];
	}
	//for (int i = 0 ; i < sizeof(array)/sizeof(array[0]); i++ ) {
	//	if (array[i]>m)
	//		m = array[i];
	//}
	return m;
}
