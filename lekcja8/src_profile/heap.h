/*
 * heap.h
 *
 *  Created on: 21-10-2016
 *      Author: wawrzyniakw
 */
#include <vector>


#ifndef HEAP_H_
#define HEAP_H_

using namespace std;

class BinaryMinHeap {
private:
	vector<InfoElement* > data;

	int getLeftChildIndex(int nodeIndex);

	int getRightChildIndex(int nodeIndex);

	int getParentIndex(int nodeIndex) ;

public:
	BinaryMinHeap();

	InfoElement* getMinimum();

	bool isEmpty();

	~BinaryMinHeap();

	void siftUp(int nodeIndex);

	void insert(InfoElement* value);

	void siftDown(int nodeIndex);

	void removeMin() ;
};



#endif /* HEAP_H_ */
