#pragma once

#include <cstddef>

#include "error.h"

template<typename T>
class List
{
private:
    // Узлы связного списка
    struct Node
    {
        T data;
        Node* next;
        Node* previous;
    };

    Node* m_first; // Указатель на первый узел
    Node* m_last; // Указатель на последний узел
    size_t m_size; // Размер списка

public:
    List();

    List(const List& other);
    ~List();

    List<T>& operator=(const List<T>& other);

    class Marker
    {
    public:
        bool hasNext() const
        {
            return m_marker->next != nullptr;
        }

        void next()
        {
            if (m_marker != nullptr)
                m_marker = m_marker->next;
        }

        T& getValue()
        {
            if (m_marker == nullptr)
                throw Error();

            return m_marker->data;
        }

        void remove()
        {
	    m_marker->previous->next = m_marker->next; //удаление ссылки от предыдущего
	    m_marker->next->previous = m_marker->previous; //удаление ссылки от следующего
	    valid = false; //чтобы не обращаться к удаленному
        }

	bool isValid() {
	    return valid;
	}

        friend class List;

    private:
	bool valid;
        List<T>::Node* m_marker;
    };

    Marker createMarker();

    void add(T value);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    void insert(size_t index, T value);
    void remove(size_t index);

    T get(size_t index) const;
    void set(size_t index, T value);

    size_t size() const;

};

template<typename T>
List<T>::List()
{
    m_first = nullptr;
    m_last = nullptr;
    m_size = 0;
}

template<typename T>
List<T>::List(const List& other)
{
    // Обновляем размер
    m_size = other.size();

    // Добавляем элементы из другого списка
    Node* runner = other.m_first;
    while (runner != nullptr)
    {
        add(runner->data);
        runner = runner->next;
    }
}

template<typename T>
typename List<T>::Marker List<T>::createMarker()
{
    List<T>::Marker m;
    m.m_marker = m_first;
    m.valid = true;
    return m;
}

template<typename T>
List<T>::~List()
{
    Node* runner = m_first;
    while (runner != nullptr)
    {
        Node* next = runner->next;
        delete runner;
        runner = next;
    }
}

template<typename T>
void List<T>::add(T value)
{
    // Ещё нет элементов
    if (m_first == nullptr)
    {
        m_first = new Node;
        m_last = m_first;
        m_first->data = value;
        m_first->next = nullptr;
        m_first->previous = nullptr;
        m_size = 1;
    }
    else
    {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;
        m_last->next = newNode;
        newNode->previous = m_last;
        m_last = newNode;
        ++m_size;
    }
}

template<typename T>
T& List<T>::operator[](size_t index)
{
    if (index < 0 || index >= m_size)
        throw BadArgument();

    Node* runner = m_first;
    for (int i = 0; i < index; i++)
        runner = runner->next;

    return runner->data;
}

template<typename T>
const T& List<T>::operator[](size_t index) const
{
    if (index < 0 || index >= m_size)
        throw BadArgument();

    Node* runner = m_first;
    for (int i = 0; i < index; i++)
        runner = runner->next;

    return runner->data;
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& other)
{
    // Рассматриваем случай присваивания самому себе
    if (this != &other)
    {
        // Обновляем размер
        m_size = other.size();

        // Удаляем исходный список
        while (m_first != nullptr)
        {
            Node* next = m_first->next;
            delete m_first;
            m_first = next;
        }

        // Добавляем элементы из другого списка
        Node* runner = other.m_first;
        while (runner != nullptr)
        {
            add(runner->data);
            runner = runner->next;
        }
    }

    return *this;
}

template<typename T>
void List<T>::insert(size_t index, T value)
{
    // Проверяем аргументы
    if (index < 0 || index >= m_size)
        throw BadArgument();

    // Доходим до элемента [index - 1]
    Node* runner = m_first;
    for (int i = 0; i < index - 1; i++)
        runner = runner->next;

    // Вставляем новый элемент
    Node* newNode = new Node;
    newNode->next = runner->next;
    newNode->previous = runner;
    runner->next->previous = newNode;
    runner->next = newNode;
    newNode->data = value;

    // Обновляем размер
    ++m_size;
}

template<typename T>
void List<T>::remove(size_t index)
{
    // Проверяем аргументы
    if (index < 0 || index >= m_size)
        throw BadArgument();

    // Доходим до элемента [index - 1]
    Node* runner = m_first;
    for (int i = 0; i < index - 1; i++)
        runner = runner->next;

    // Удаляем элемент и обновляем указатели
    Node* tmp = runner->next->next;
    delete runner->next;
    runner->next = tmp;
    runner->next->previous = runner;

    // Обновляем размер
    --m_size;
}

template<typename T>
T List<T>::get(size_t index) const
{
    return operator[](index);
}

template<typename T>
void List<T>::set(size_t index, T value)
{
    operator[](index) = value;
}

template<typename T>
size_t List<T>::size() const
{
    return m_size;
}
