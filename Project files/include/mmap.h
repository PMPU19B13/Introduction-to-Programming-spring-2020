#pragma once

#include <queue>
#include "pair.h"
#include "error.h"

template<typename K, typename V>
class MMap
{
public:
	MMap();

	~MMap();

	void add(const K& key, const V& value);

	bool hasKey(const K& key) const;

	const V& getAssoc(const K& key);

	void traverse(void (* action)(int));

private:
	struct Node
	{
		Pair<K, V> data;
		Node* left; // Указатель на корень левого поддерева
		Node* right; // Указатель на корень правого поддерева
	};

	Node* m_root; // Указатель на корневой узел

	void clear(Node* runner);

	void traversePrivate(Node* runner, void (* action)(int));
};

template<typename K, typename V>
MMap<K, V>::MMap() : m_root(nullptr)
{
}

template<typename K, typename V>
MMap<K, V>::~MMap()
{
	clear(m_root);
}

template<typename K, typename V>
void MMap<K, V>::traverse(void (* action)(int)) 
{
	traversePrivate(m_root, action);
}


template <typename K, typename V>
void MMap<K, V>::traversePrivate(Node* runner, void (* action)(int)) 
{
	if (runner == nullptr) return;
	std::queue<Node*> q;
	q.push(runner);

	while (q.empty() == false) 
	{
		Node* node = q.front();
		// Perform action here
		q.pop();

		if (node->left != nullptr) q.push(node->left);
		if (node->right != nullptr) q.push(node->right);
	}
}


template<typename K, typename V>
void MMap<K, V>::add(const K& key, const V& value)
{
	if (m_root == nullptr)
	{
		m_root = new Node;

		m_root->data.key = key;
		m_root->data.value = value;
		m_root->left = nullptr;
		m_root->right = nullptr;
		return;
	}

	Node* runner = m_root;

	while (true)
	{
		if (runner->data.key < key) // Двигаемся по правой ветке
		{
			if (runner->right != nullptr)
			{
				runner = runner->right;
				continue;
			}
			else
			{
				runner->right = new Node;
				runner = runner->right;

				runner->data.key = key;
				runner->data.value = value;
				runner->left = nullptr;
				runner->right = nullptr;
				return;
			}
		}
		else // Двигаемся по левой ветке
		{
			if (runner->left != nullptr)
			{
				runner = runner->left;
				continue;
			}
			else
			{
				runner->left = new Node;
				runner = runner->left;

				runner->data.key = key;
				runner->data.value = value;
				runner->left = nullptr;
				runner->right = nullptr;
				return;
			}
		}
	}
}

template<typename K, typename V>
bool MMap<K, V>::hasKey(const K& key) const // Проверка наличия пары с указанным ключом
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
const V& MMap<K, V>::getAssoc(const K& key)
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
void MMap<K, V>::clear(Node* runner)
{
	if (runner != nullptr)
	{
		clear(runner->left);
		clear(runner->right);
		delete runner;
	}
}