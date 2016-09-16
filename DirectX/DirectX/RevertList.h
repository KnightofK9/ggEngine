#pragma once
#include "RevertLinkedList.h"
template <class T>
class RevertList {
public:
	RevertList();
	~RevertList();
	void push(T item);
	T pop();
	T next();
	void slice(unsigned int start, unsigned int end);
	int remove(T item);
private:
	RevertLinkedList<T> *pHead;
	RevertLinkedList<T> *pTail;
	RevertLinkedList<T> *pCurrent;
	RevertLinkedList<T> *createRevertLinkedList(T item);
};

template<class T>
inline RevertList<T>::RevertList()
{
	pHead = 0;
	pTail = 0;
	pCurrent = 0;
}

template<class T>
inline RevertList<T>::~RevertList()
{
	RevertLinkedList<T> *p = pHead;
	while (p != 0) {
		RevertLinkedList<T> *pT = p;
		p = p->pNext;
		delete pT;
	}
}

template<class T>
inline void RevertList<T>::push(T item)
{
	RevertLinkedList<T> *linked = createRevertLinkedList(item);
	if (pHead == pTail && pHead == NULL) {
		pHead = pTail = linked;
		return;
	}
	pTail->pNext = linked;
	linked->pPrev = pTail;
	pTail = linked;
}

template<class T>
inline T RevertList<T>::pop()
{

}

template<class T>
inline T RevertList<T>::next()
{
	if (pCurrent == NULL) pCurrent = pHead;
	pCurrent = pCurrent->pNext;
	if (pCurrent != NULL) {
		return pCurrent->content;
	}
}

template<class T>
inline void RevertList<T>::slice(unsigned int start, unsigned int end)
{

}

template<class T>
inline int RevertList<T>::remove(T item)
{
	return 0;
}

template<class T>
inline RevertLinkedList<T>* RevertList<T>::createRevertLinkedList(T item)
{
	RevertLinkedList<T> linked;
	linked.content = item;
	linked.pNext = NULL;
	linked.pPrev = NULL;
	linked.pDown = NULL;
	return &linked;
}
