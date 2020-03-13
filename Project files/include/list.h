#pragma once

#include <cstddef>

#include "error.h"

template<typename T>
class List
{
private:
    struct Node
    {
        T data;
        Node* next;
    };

    Node* m_first; // Указатель на первый узел
    size_t m_size; // Размер списка
    Node* m_marker;

public:
    List();

    List(const List& other);
    ~List();

    List<T>& operator=(const List<T>& other);

    class Marker
    {
    public:
        bool canMoveNext() const
        {
            return m_marker->next != nullptr;
        }

        void moveNext()
        {
            if (m_marker != nullptr)
                m_marker = m_marker->next;
        }

        T& getCurrentValue()
        {
            if (m_marker == nullptr)
                throw Error();

            return m_marker->data;
        }

        friend class List;

    private:
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


//    void removeCurrent();
};

template<typename T>
List<T>::List()
{
    m_first = nullptr;
    m_size = 0;
    m_marker = nullptr;
}

template<typename T>
List<T>::List(const List& other)
{
    // Обновляем размер
    m_size = other.size();

    // Добавляем элементы из другого списка
    // TODO: Оптимизировать до O(n)
    // Сейчас при копировании мы проходим список n^2/2 раз. Уменьшить до n
    for (size_t i = 0; i < other.size(); i++)
        add(other[i]);
}

template<typename T>
typename List<T>::Marker List<T>::createMarker()
{
    List<T>::Marker m;
    m.m_marker = m_first;
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
        m_first->data = value;
        m_first->next = nullptr;
        m_size = 1;
    }
    else
    {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;
        Node* runner = m_first;
        while (runner->next != nullptr)
            runner = runner->next;
        runner->next = newNode;
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
        // TODO: Оптимизировать до O(n)
        // Сейчас при копировании мы проходим список n^2/2 раз. Уменьшить до n
        for (size_t i = 0; i < other.size(); i++)
            add(other[i]);
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

    // Обновляем размер
    --m_size;
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

//template<typename T>
//void List<T>::rewind()
//{
//    m_marker = m_first;
//}

//template<typename T>
//bool List<T>::canMoveNext() const
//{
//    return m_marker->next != nullptr;
//}

//template<typename T>
//void List<T>::moveNext()
//{
//    if (m_marker != nullptr)
//        m_marker = m_marker->next;
//}

//template<typename T>
//T& List<T>::getCurrentValue()
//{
//    if (m_marker == nullptr)
//        throw Error();
//
//    return m_marker->data;
//}

//template<typename T>
//void List<T>::removeCurrent()
//{
//    if (m_marker != nullptr)
//    {
//        // TODO; Implement
//    }
//}