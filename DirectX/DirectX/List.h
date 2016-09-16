#pragma once
#include "LinkedList.h"
template <class T>
class List {
public:
	List();
	~List();
	void push(T item);
	T pop();
	T next();
	void slice(unsigned int start, unsigned int end);
	int remove(T item);
private:
	LinkedList<T> *pHead;
	LinkedList<T> *pTail;
	LinkedList<T> *pCurrent;
	LinkedList<T> *createLinkedList(T item);
};

template<class T>
inline List<T>::List()
{
	pHead = NULL;
	pTail = NULL;
	pCurrent = NULL;
}

template<class T>
inline List<T>::~List()
{
	LinkedList<T> *p = pHead;
	while (p != NULL) {
		LinkedList<T> *pT = p;
		p = p->pNext;
		delete pT;
	}
}

template<class T>
inline void List<T>::push(T item)
{
	LinkedList<T> *linked = createLinkedList(item);
	if (pHead == pTail && pHead == NULL) {
		pHead = pTail = linked;
		return;
	}
	pTail->pNext = linked;
	linked->pPrev = pTail;
	pTail = linked;
}

template<class T>
inline T List<T>::pop()
{

}

template<class T>
inline T List<T>::next()
{
	if (pCurrent == NULL) pCurrent = pHead;
	pCurrent = pCurrent->pNext;
	if (pCurrent != NULL) {
		return pCurrent->content;
	}
}

template<class T>
inline void List<T>::slice(unsigned int start, unsigned int end)
{

}

template<class T>
inline int List<T>::remove(T item)
{
	return 0;
}



template<class T>
inline LinkedList<T>* List<T>::createLinkedList(T item)
{
	LinkedList<T> linked;
	linked.content = item;
	linked.pNext = NULL;
	linked.pPrev = NULL;
	return &linked;
}


