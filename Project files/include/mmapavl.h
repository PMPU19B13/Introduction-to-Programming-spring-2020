#pragma once

#include "pair.h"
#include "error.h"
#include <stdlib.h>

template<typename K, typename V>
class MMapAVL
{
public:
	MMapAVL();
	~MMapAVL();
	void add(const K& key, const V& value);
	bool hasKey(const K& key) const;
	const V& getAssoc(const K& key);

private:
	struct Node
	{
		Pair<K, V> data;
		int height; // Высота поддерева
		Node* left, * right, * parent = nullptr;
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
		Node* t = tree->right;
		t->parent = tree->parent;
		tree->right = t->left;
		t->left = tree;
		tree->parent = t;
		tree->height = std::max(height(tree->left), height(tree->right)) + 1;
		t->height = std::max(height(t->left), height(t->right)) + 1;
		return t;
	}

	Node* rotateRight(Node* tree)
	{
		Node* t = tree->left;
		t->parent = tree->parent;
		tree->left = t->right;
		t->right = tree;
		tree->parent = t;
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

	Node* add(Node* prev, Node* tree, const K& key, const V& value)
	{
		if (tree == nullptr)
		{
			tree = new Node;
			tree->data.key = key;
			tree->data.value = value;
			tree->left = nullptr;
			tree->right = nullptr;
			tree->parent = prev;
			tree->height = 1;
			return tree;
		}
		if (key < tree->data.key)
		{
			tree->left = add(tree, tree->left, key, value);
		}
		else
		{
			tree->right = add(tree, tree->right, key, value);
		}
		return balanceTree(tree);
	}
};

template<typename K, typename V>
void MMapAVL<K, V>::add(const K& key, const V& value)
{
	m_root = add(nullptr, m_root, key, value);
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
