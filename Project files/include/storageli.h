#pragma once

#include <stddef.h>
#include "error.h"

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
        Node* next;
    };

    Node* m_first;
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

    ~StorageLi()
    {
        Node* ptr = m_first;
        while (ptr != nullptr)
        {
            Node* next = ptr->next;
            delete ptr;
            ptr = next;
        }
    }

    void AddElem(T val)
    {
        // Ещё нет элементов
        if (m_first == nullptr)
        {
            m_first = new Node;
            m_first->data = val;
            m_first->next = nullptr;
            m_size = 1;
        }
        else
        {
            Node* newnode = new Node;
            newnode->data = val;
            newnode->next = nullptr;
            Node* runner = m_first;
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

    T& operator[] (size_t num) const
    {
        if (num < m_size)
        {
            Node* ptr = m_first;
            for (int i = 0; i < num; i++)
            {
                ptr = ptr->next;
            }
            return ptr->data;
        }
        else
        {
            throw(Error());
        }
    }

    void operator=(const StorageLi<T>& orig)
    {
        m_size = orig.TotalSize();
        while (m_first != nullptr)
        {
            Node* next = m_first->next;
            delete m_first;
            m_first = next;
        }
        for (size_t i = 0; i < orig.TotalSize(); i++)
        {
            AddElem(orig[i]);
        }
    }

    void InsertElemByNum(size_t num, T val)
    {
        if (num < m_size)
        {
            Node* ptr = m_first;
            for (int i = 0; i < num - 1; i++)
            {
                ptr = ptr->next;
            }
            Node* newnode = new Node;
            newnode->next = ptr->next;
            ptr->next = newnode;
            newnode->data = val;
            ++m_size;
        }
        else
        {
            throw(Error());
        }
    }
    void DelElemByNum(size_t num)
    {
        if (num < m_size)
        {
            Node* ptr = m_first;
            for (int i = 0; i < num - 1; i++)
            {
                ptr = ptr->next;
            }
            Node* tmp = ptr->next->next;
            delete ptr->next;
            ptr->next = tmp;
            --m_size;
        }
        else
        {
            throw(Error());
        }
    }

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
}*/
