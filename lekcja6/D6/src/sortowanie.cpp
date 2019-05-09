#include "./sortowanie.hpp"


void sortowanie(int array[], int w)
{
	int i,m,n;
	for (i =1 ; i<w; i++) {
		m = array[i];
		for(n = i-1; n >= 0; n--) {
			if(m < array[n]) {
				array[n+1] = array[n];
			}
			else
				break;
		}
		array[n+1] = m;
	}
}
