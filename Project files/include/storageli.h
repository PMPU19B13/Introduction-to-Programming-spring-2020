#pragma once

#include <stddef.h>

#ifdef DEBUG
#include <iostream>
#endif

template<typename T>
class StorageLi
{
private:
    struct Node
    {
        T data;
        Node *next;
    };

    Node *m_first;
    size_t m_size;

public:
    StorageLi()
    {
        m_first = nullptr;
        m_size = 0;
#ifdef DEBUG
        std::cout << "StorageLi constructor called" << std::endl;
#endif
    }

    void AddElem(T val)
    {
        // Ещё нет элементов
        if (m_first == nullptr)
        {
            m_first = new Node;
            m_first->data = val;
            m_size = 1;
        }
        else
        {
            Node *newnode = new Node;
            newnode->data = val;
            newnode->next = nullptr;
            Node *runner = m_first;
            while (runner->next != nullptr)
                runner = runner->next;
            runner->next = newnode;
            ++m_size;
        }
    };

    size_t TotalSize() const
    {
        return m_size;
    };

};
/*
bool testStorage4() {
	Storage<int> storage;
	for (int k = 0; k < 4; k++) {
		storage.AddElem(k);
	}
	if (storage.TotalSize() != 4) return false;
	for (int k = 0; k < 4; k++) {
		if (storage.GetElemByNum(k) != k) {
			return false;
		}
	}
	return true;
}
*/
