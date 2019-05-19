/*
 * heap.cpp
 *
 *  Created on: 21-10-2016
 *      Author: wawrzyniakw
 */
#include "infoelement.h"
#include "heap.h"

using namespace std;

int BinaryMinHeap::getLeftChildIndex(int nodeIndex) {
	return 2 * nodeIndex + 1;
}

int BinaryMinHeap::getRightChildIndex(int nodeIndex) {
	return 2 * nodeIndex + 2;
}

int BinaryMinHeap::getParentIndex(int nodeIndex) {
	return (nodeIndex - 1) / 2;
}

BinaryMinHeap::BinaryMinHeap() {
}

//przyspieszono
InfoElement* BinaryMinHeap::getMinimum() {
    if (isEmpty())
      return 0;

    return data[0];
}

bool BinaryMinHeap::isEmpty() {
	return (data.size() == 0);
}

BinaryMinHeap::~BinaryMinHeap() {
}

void BinaryMinHeap::siftUp(int nodeIndex) {
	int parentIndex;
	InfoElement *tmp;
	if (nodeIndex != 0) {
		parentIndex = getParentIndex(nodeIndex);
		InfoElement *a = data[parentIndex];
		InfoElement *b = data[nodeIndex];

		if (a->time > b->time) {
			tmp = data[parentIndex];
			data[parentIndex] = data[nodeIndex];
			data[nodeIndex] = tmp;
			siftUp(parentIndex);
		}
	}
}

void BinaryMinHeap::insert(InfoElement *value) {
	data.push_back(value);
	int a = data.size() - 1;
	siftUp(a);
}

void BinaryMinHeap::siftDown(int nodeIndex) {
	int leftChildIndex, rightChildIndex, minIndex;
	InfoElement *tmp;
	leftChildIndex = getLeftChildIndex(nodeIndex);
	rightChildIndex = getRightChildIndex(nodeIndex);
	if (rightChildIndex >= data.size()) {
		if (leftChildIndex >= data.size())
			return;
		else
			minIndex = leftChildIndex;
	} else {
		InfoElement *a = data[leftChildIndex];
		InfoElement *b = data[rightChildIndex];
		if (a->time <= b->time)
			minIndex = leftChildIndex;
		else
			minIndex = rightChildIndex;
	}

	InfoElement *a = data[nodeIndex];
	InfoElement *b = data[minIndex];
	if (a->time > b->time) {
		tmp = data[minIndex];
		data[minIndex] = data[nodeIndex];
		data[nodeIndex] = tmp;
		siftDown(minIndex);
	}
}

void BinaryMinHeap::removeMin() {
	if (isEmpty())
		return;
	else {
		data[0] = data[data.size() - 1];
		data.pop_back();
		if (data.size() > 0)
			siftDown(0);
	}
}

