#pragma once
#include "pair.h"
#include "error.h"
#include <stdlib.h>
#include <algorithm>

template<typename K, typename V>
class MMapAVL
{
private:
    struct Node
    {
        Pair<K, V> data;
        int height; // Высота поддерева
        Node* left; // Указатель на корень левого поддерева
        Node* right; // Указатель на корень правого поддерева
        Node* parent; // Указатель на родительский элемент
    };

    Node* m_root; // Указатель на корневой узел

    void clear(Node* runner);

    int height(Node* tree)
    {
        if (tree == nullptr)
            return 0;
        return tree->height;
    }

    int balanceFactor(Node* tree)
    {
        return height(tree->right) - height(tree->left);
    }

    Node* rotateLeft(Node* tree)
    {
        Node* p = tree->parent;
        Node* t = tree->right;

        tree->right = t->left;
        t->left = tree;
        tree->parent = p;
        tree->height = std::max(height(tree->left), height(tree->right)) + 1;
        t->height = std::max(height(t->left), height(t->right)) + 1;
        return t;
    }

    Node* rotateRight(Node* tree)
    {
        Node* t = tree->left;
        Node* p = tree->parent;
        tree->left = t->right;
        t->right = tree;
        tree->parent = p;
        tree->height = std::max(height(tree->left), height(tree->right)) + 1;
        t->height = std::max(height(t->left), height(t->right)) + 1;
        return t;
    }

    Node* balanceTree(Node* tree)
    {
        tree->height = std::max(height(tree->left), height(tree->right)) + 1;
        if (balanceFactor(tree) == 2)
        {
            if (balanceFactor(tree->right) < 0)
                tree->right = rotateRight(tree->right);
            return rotateLeft(tree);
        }
        if (balanceFactor(tree) == -2)
        {
            if (balanceFactor(tree->left) > 0)
                tree->left = rotateLeft(tree->left);
            return rotateRight(tree);
        }
        return tree;
    }

    Node* add(Node* tree, Node* p, const K& key, const V& value)
    {
        if (tree == nullptr)
        {
            tree = new Node;
            tree->data.key = key;
            tree->data.value = value;
            tree->left = nullptr;
            tree->right = nullptr;
            tree->parent = p;
            tree->height = 1;
            return tree;
        }
        if (key < tree->data.key)
            tree->left = add(tree->left, tree, key, value);
        else
            tree->right = add(tree->right, tree, key, value);
        return balanceTree(tree);
    }

public:
    MMapAVL();
    ~MMapAVL();
    void add(const K& key, const V& value);
    bool hasKey(const K& key) const;
    const V& getAssoc(const K& key);


    class Marker
    {
    public:
        bool hasNext() const
        {
            if (m_marker == nullptr)
                throw Error();
            Node* runner = m_root;
            while (runner->right != nullptr) runner = runner->right;
            return m_marker->data.key < runner->data.key;
        }

        void next()
        {
            if (m_marker == nullptr || !hasNext())
            {
                m_marker = nullptr;
                return;
            }
            if (m_marker->right != nullptr) {
                m_marker = m_marker->right;
                while (m_marker->left != nullptr) m_marker = m_marker->left;
            }
            else
            {
                Node* runner = m_marker->parent;
                while (runner->data.key < m_marker->data.key) runner = runner->parent;
                m_marker = runner;
            }
        }

        V& getValue()
        {
            if (m_marker == nullptr)
                throw Error();

            return m_marker->data;
        }

        void remove()
        {
            remove(m_root);
            valid = false;
        }

        Node* getMin(Node* n)
        {
            if (!n->left) return n;
            return getMin(n->left);
        }

        void remove(Node* runner)
        {
            if (m_marker == nullptr)
                throw Error();
            if (runner->data.key > m_marker->data.key) remove(runner->left);
            else if (runner->data.key < m_marker->data.key) remove(runner->right);
            else {
                if (!(runner->right) && !(runner->left))
                {
                    Node* n = runner;
                    if (n->parent != nullptr) n->parent->height = --(n->parent->height);
                    while (n != m_root) {
                        n->parent->height = std::max(n->parent->left->height, n->parent->right->height);
                        n = n->parent->height;
                    }
                    if (runner->parent->left->data.key == runner->data.key)
                    {
                        runner->parent->left = nullptr;
                        free(runner);
                        return;
                    }
                    else
                    {
                        runner->parent->right = nullptr;
                        free(runner);
                        return;
                    }
                }
                if (!runner->right)
                {
                    Node* n = runner;
                    if (n->parent != nullptr) n->parent->height = --(n->parent->height);
                    while (n != m_root) {
                        n->parent->height = std::max(n->parent->left->height, n->parent->right->height);
                        n = n->parent->height;
                    }
                    if (runner->parent->left->data.key == runner->data.key)
                    {
                        runner->parent->left = runner->left;
                        runner->left->parent = runner->parent;
                        free(runner);
                        return;
                    }
                    else
                    {
                        runner->parent->right = runner->left;
                        runner->left->parent = runner->parent;
                        free(runner);
                        return;
                    }
                }
                if (!runner->left)
                {
                    Node* n = runner;
                    if (n->parent != nullptr) n->parent->height = --(n->parent->height);
                    while (n != m_root) {
                        n->parent->height = std::max(n->parent->left->height, n->parent->right->height);
                        n = n->parent->height;
                    }
                    if (runner->parent->left->data.key == runner->data.key)
                    {
                        runner->parent->left = runner->right;
                        runner->right->parent = runner->parent;
                        free(runner);
                        return;
                    }
                    else
                    {
                        runner->parent->right = runner->right;
                        runner->right->parent = runner->parent;
                        free(runner);
                        return;
                    }
                }
                Node* t = runner;
                runner = getMin(t->right);
                Node* n = runner;
                if (n->parent != nullptr) n->parent->height = --(n->parent->height);
                while (n != m_root) {
                    n->parent->height = std::max(n->parent->left->height, n->parent->right->height);
                    n = n->parent->height;
                }
                if (runner->parent->left->data.key == runner->data.key)
                {
                    runner->parent->left = runner->right;
                }
                else
                {
                    runner->parent->right = runner->right;
                }
                runner->right = t->right;
                runner->left = t->left;
                runner->parent = t->parent;
                if (t->parent->left->data.key == t->data.key)
                {
                    t->parent->left = runner;
                }
                else
                {
                    t->parent->right = runner;
                }
                runner->right->parent = runner;
                runner->left->parent = runner;
                runner->parent->height--;
                free(t);
                balanceTree(runner);
                return;
            }

            balanceTree(runner);
        }

        bool isValid()
        {
            return m_marker != nullptr && valid;
        }

        friend class MMapAVL<K, V>;

    private:
        bool valid;
        MMapAVL<K, V>::Node* m_marker;
    };

    Marker createMarker();

};

template<typename K, typename V>
typename MMapAVL<K, V>::Marker MMapAVL<K, V>::createMarker()
{
    MMapAVL<K, V>::Marker m;

    while (m.m_marker->left != nullptr) m.m_marker = m.m_marker->left;
    m.valid = true;
    return m;
}

template<typename K, typename V>
void MMapAVL<K, V>::add(const K& key, const V& value)
{
    m_root = add(m_root, nullptr, key, value);
}

template<typename K, typename V>
MMapAVL<K, V>::MMapAVL() : m_root(nullptr)
{
}

template<typename K, typename V>
MMapAVL<K, V>::~MMapAVL()
{
    clear(m_root);
}


template<typename K, typename V>
bool MMapAVL<K, V>::hasKey(const K& key) const // Проверка наличия пары с указанным ключом
{

    Node* runner = m_root;
    if (runner == nullptr)
        return false;

    while (true)
    {
        if (runner->data.key == key)
            return true;

        if (runner->data.key < key) // Двигаемся по правой ветке
        {
            if (runner->right == nullptr)
                return false;

            runner = runner->right;
        }
        else // Двигаемся по левой ветке
        {
            if (runner->left == nullptr)
                return false;

            runner = runner->left;
        }
    }
}

template<typename K, typename V>
const V& MMapAVL<K, V>::getAssoc(const K& key)
{
    Node* runner = m_root;
    if (runner == nullptr)
        throw BadArgument();

    while (true)
    {
        if (runner->data.key == key)
            return runner->data;

        if (runner->data.key < key) // Двигаемся по правой ветке
        {
            if (runner->right == nullptr)
                throw BadArgument(); // Не нашли такого ключа

            runner = runner->right;
        }
        else // Двигаемся по левой ветке
        {
            if (runner->left == nullptr)
                throw BadArgument(); // Не нашли такого ключа

            runner = runner->left;
        }
    }
}

template<typename K, typename V>
void MMapAVL<K, V>::clear(Node* runner)
{
    if (runner != nullptr)
    {
        clear(runner->left);
        clear(runner->right);
        delete runner;
    }
}
