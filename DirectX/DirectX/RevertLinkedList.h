#pragma once
template <class T>
struct RevertLinkedList {
	RevertLinkedList *pNext;
	RevertLinkedList *pPrev;
	RevertLinkedList *pDown;
	T *content;
};
