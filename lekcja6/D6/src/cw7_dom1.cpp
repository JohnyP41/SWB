#include "./cw7_dom1.hpp"
#include "./sortowanie.hpp"
#include "../libs/libswbmath/max.h"
#include "../libs/libswbmath/min.h"
#include "../libs/libswbmath/avg.h"

using namespace std;

int main()
{
	int a[] = {3,11,13,2,4,1,5, 10, 12};
	int w = (sizeof(a)/sizeof(*a));
	cout<<max(a, w)<<endl;
	cout<<min(a, w)<<endl;
	cout<<avg(a, w)<<endl;

	for (int i = 0 ; i< w; i++) {
		cout<<a[i]<<" ";
	}
	cout<<endl;

	sortowanie(a, w);

	for (int i = 0 ; i< w; i++) {

                cout<<a[i]<<" ";
        }
	cout<<endl;

	return 0;
}

