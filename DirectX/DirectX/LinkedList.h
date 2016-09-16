#pragma once
template <class T>
struct LinkedList {
	LinkedList *pNext;
	LinkedList *pPrev;
	T *content;
};

