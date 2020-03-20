#pragma once

template<typename K, typename V>
class MMap
{
public:
	MMap() : m_root(nullptr)
	{}

	~MMap()
	{
		clear(m_root);
	}

	void add(const K& k, const V& v)
	{
		if (m_root == nullptr)
		{
			m_root = new Node;

			m_root->key = k;
			m_root->data = v;
			m_root->left = nullptr;
			m_root->right = nullptr;
			return;
		}

		Node* runner = m_root;

		while (true)
		{
			if (runner->key < k)
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

					runner->key = k;
					runner->data = v;
					runner->left = nullptr;
					runner->right = nullptr;
					return;
				}
			}
			else
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

					runner->key = k;
					runner->data = v;
					runner->left = nullptr;
					runner->right = nullptr;
					return;
				}
			}
		}

	}

	bool hasKey(const K& k) // Проверка наличия пары с указанным ключом
	{
		Node* runner = m_root;
		if (runner == nullptr)
			return false;

		while (true)
		{
			if (runner->key == k)
				return true;

			if (runner->key < k) // Двигаемся по правой ветке
			{
				if (runner->right == nullptr)
					return false; // Не нашли такого ключа

				runner = runner->right;
			}
			else
			{
				if (runner->left == nullptr)
					return false;

				runner = runner->left;
			}
		}
	}

	const V& getAssoc(const K& k)
	{
		Node* runner = m_root;
		if (runner == nullptr)
			throw BadArgument();

		while (true)
		{
			if (runner->key == k)
				return runner->data;

			if (runner->key < k) // Двигаемся по правой ветке
			{
				if (runner->right == nullptr)
					throw BadArgument(); // Не нашли такого ключа

				runner = runner->right;
			}
			else
			{
				if (runner->left == nullptr)
					throw BadArgument();

				runner = runner->left;
			}
		}
	}

private:
	struct Node
	{
		// TODO: Заменить на Pair<K, V>
		K key;
		V data;
		Node* left;
		Node* right;
	};

	Node* m_root;

	void clear(Node* runner)
	{
		if (runner != nullptr)
		{
			clear(runner->left);
			clear(runner->right);
			delete runner;
		}
	}
};
