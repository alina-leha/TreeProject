#pragma once
#include <iostream>

using namespace std;

template <class Key = int, class Data = int>
class Tree {
private:

	class Node {
	public:
		Key key;
		Data data;
		Node* left, * right;

		explicit Node(Key key, Data data = Data(), Node* left = nullptr, Node* right = nullptr) : key(key), data(data), left(left), right(right) {}
	};

	static int COUNTER;

	int size;
	Node* root;

	void copy(Node* node);
	void clear(Node* node);
	bool insert(Key key, Data data, Node* parent, Node* current);
	Node* getNode(Key key, Node* current);
	bool remove(Key key, Node* parent, Node* current);
	Node* maxWithDel(Node* parent, Node* current);
	void print(Node* node, int lvl);
	void printKeys(Node* node);
	Node* lesserParent(Node* current, Node* target);
	Node* biggerParent(Node* current, Node* target);
	Node* getNode(Key key);
	Node* getNext(Node* node);
	Node* getPrev(Node* node);
	Node* rotateLeft(Node* oldRoot);
	Node* rotateRight(Node* oldRoot);
	Node* insertRoot(Key key, Data data, Node* node, bool& success);

	static void incrementCOUNTER();

public:
	Tree(); //Конструктор
	Tree(Tree& t); //Конструктор копирования
	~Tree();	//Деструктор

	static int getCOUNTER();	//Опрос числа узлов дерева, просмотренных операцие
	static void	resetCOUNTER();	//Сброс числа узлов дерева, просмотренных операцией
	void clear();				//Очистка дерева
	int getSize();				//Опрос размера дерева
	bool isEmpty();				//Проверка дерева на пустоту
	bool insert(Key key, Data data); //Включение данных с заданным ключом
	bool remove(Key key);				//Удаление данных с заданным ключом
	Data find(Key key);					//Чтение по ключу
	bool set(Key key, Data data);			//Запись по ключу
	Node* min(Node* node);
	Node* max(Node* node);
	void print();
	void printKeys();		//Формирование списка ключей в дереве в порядке L->t->R
	Node* getRoot();
	Node* insertRoot(Key key, Data data, bool& success); // Вставка в корень дерева элемента с ключом, большим заданного значения.

	class Iterator {
	private:
		Tree* tree;
		Node* node;

	public:
		explicit Iterator(Tree<Key, Data>* tree = nullptr, Node* node = nullptr) : tree(tree), node(node) {}

		bool operator++(int);			//Операция перехода к следующему по ключу узлу в дереве
		bool operator--(int);			//Операция перехода к предыдущему по ключу узлу в дереве
		bool operator==(Iterator it);	//Проверка равенства однотипных итераторов	
		bool operator==(Node* node);
		bool operator!=(Iterator it);	//Проверка неравенства однотипных итераторо
		Data& operator*(); // Операция чтения и записи данных текущего узла
	};

	class rIterator {
	private:
		Tree* tree;
		Node* node;

	public:
		explicit rIterator(Tree<Key, Data>* tree = nullptr, Node* node = nullptr) : tree(tree), node(node) {}

		bool operator++(int);  //Операция перехода к предыдущему по ключу узлу в дереве
		bool operator--(int);  //Операция перехода к следующему по ключу узлу в дереве
		bool operator==(rIterator rit);
		bool operator==(Node* node);  //Проверка равенства однотипных итераторов
		bool operator!=(rIterator ri);  //Проверка неравенства однотипных итераторовt
		Data& operator*();			// Операция чтения и записи данных текущего узла
	};

	friend class Iterator;
	friend class rIterator;

	void print(Node* node, int lvl, Iterator& iter);
	void print(Node* node, int lvl, rIterator& riter);

	Iterator begin();				//Запрос прямого итератора, установленного на узел дерева с минимальным ключом
	Iterator end();				//Запрос ‘неустановленного’ прямого итератора

	rIterator rbegin();				//Запрос обратного итератора, установленного на узел дерева с максимальным ключом
	rIterator rend();				//Запрос ‘неустановленного’ обратного итератора
};

//-------------------Tree---------------------//

template <class Key, class Data>
int Tree<Key, Data>::COUNTER = 0;

template <class Key, class Data>
void Tree<Key, Data>::incrementCOUNTER() {
	COUNTER++;
}

template <class Key, class Data>
void Tree<Key, Data>::resetCOUNTER() {
	COUNTER = 0;
}

template <class Key, class Data>
int Tree<Key, Data>::getCOUNTER() {
	return COUNTER;
}

template <class Key, class Data>
Tree<Key, Data>::Tree() {
	this->size = 0;
	this->root = nullptr;
}

template <class Key, class Data>
Tree<Key, Data>::Tree(Tree<Key, Data>& t) {
	this->size = 0;
	this->root = nullptr;
	copyConstruct(t.root);
}

template <class Key, class Data>
Tree<Key, Data>::~Tree() {
	if (!this->isEmpty())
		this->clear();
}

template <class Key, class Data>
void Tree<Key, Data>::copy(Node* node) {
	insert(node->key, node->data);
	if (node->left)
		copy(node->left);
	if (node->right)
		copy(node->right);
}

template <class Key, class Data>
void Tree<Key, Data>::clear(Node* node) {
	if (node) {
		this->clear(node->left);
		this->clear(node->right);
		delete node;
		this->size--;
	}
}

template <class Key, class Data>
void Tree<Key, Data>::clear() {
	this->clear(this->root);
	this->root = nullptr;
	size = 0;
}

template <class Key, class Data>
int Tree<Key, Data>::getSize() {
	return this->size;
}

template <class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::getRoot() {
	return this->root;
}

template <class Key, class Data>
bool Tree<Key, Data>::isEmpty() {
	return this->size == 0;
}

template <class Key, class Data>
bool Tree<Key, Data>::insert(Key key, Data data) {
	if (!insert(key, data, nullptr, root))
		return false;

	this->size++;
	return true;
}

template <class Key, class Data>
bool Tree<Key, Data>::insert(Key key, Data data, Tree<Key, Data>::Node* parent, Tree<Key, Data>::Node* current) {
	if (!current && parent == nullptr)
		root = new Node(key, data);

	else if (!current) {
		current = new Node(key, data);
		key < parent->key ? parent->left = current : parent->right = current;
	}

	else {
		Tree<Key, Data>::incrementCOUNTER();

		if (key < current->key) {
			if (!insert(key, data, current, current->left))
				return false;
		}
		else if (key > current->key) {
			if (!insert(key, data, current, current->right))
				return false;
		}
		else
			return false;
	}

	return true;
}

template <class Key, class Data>
bool Tree<Key, Data>::remove(Key key) {
	if (!root)
		return false;

	if (key == root->key && !root->left && !root->right) {
		delete root;
		root = nullptr;
	}
	else if (!remove(key, nullptr, root)) {
		return false;
	}
	else {
		Tree<Key, Data>::incrementCOUNTER();
	}

	this->size--;
	return true;
}

template <class Key, class Data>
bool Tree<Key, Data>::remove(Key key, Node* parent, Node* current) {
	if (!current)
		return false;

	if (key == current->key && !parent) {
		if (root->left) {
			if (root->left->right) {
				Node* node = maxWithDel(root->left, root->left->right);
				node->right = root->right;
				node->left = root->left;

				delete root;
				root = node;
			}
			else {
				root->left->right = root->right;

				Node* node = root->left;

				delete root;
				root = node;
			}
		}
		else {
			Node* node = root->right;
			delete root;
			root = node;
		}
	}
	else {
		if (key == current->key) {
			if (current->left) {
				if (current->left->right) {
					Node* node = maxWithDel(current->left, current->left->right);
					node->right = current->right;
					node->left = current->left;

					if (parent->left == current)
						parent->left = node;
					else
						parent->right = node;
					delete current;
				}
				else {
					current->left->right = current->right;

					if (parent->left == current)
						parent->left = current->left;
					else
						parent->right = current->left;
					delete current;
				}
			}
			else {
				if (parent->left == current)
					parent->left = current->right;
				else
					parent->right = current->right;
				delete current;
			}
		}
		else if (key < current->key) {
			Tree<Key, Data>::incrementCOUNTER();
			if (!remove(key, current, current->left))
				return false;
		}
		else {
			Tree<Key, Data>::incrementCOUNTER();
			if (!remove(key, current, current->right))
				return false;
		}
	}

	return true;
}

template <class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::maxWithDel(Node* parent, Node* current) {
	if (!current)
		return nullptr;

	while (current->right) {
		Tree<Key, Data>::incrementCOUNTER();
		parent = current;
		current = current->right;
	}

	if (current->left) {
		parent->right = current->left;
		current->left = nullptr;
	}
	else {
		parent->right = nullptr;
	}

	return current;
}

template <class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::getNode(Key key) {
	return getNode(key, root);
}

template <class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::getNode(Key key, Node* node) {
	if (!node)
		return nullptr;

	if (key == node->key)
		return node;
	else if (key < node->key) {
		Tree<Key, Data>::incrementCOUNTER();
		node = getNode(key, node->left);
	}
	else {
		Tree<Key, Data>::incrementCOUNTER();
		node = getNode(key, node->right);
	}

	return node;
}

template <class Key, class Data>
Data Tree<Key, Data>::find(Key key) {
	Node* node = getNode(key);

	if (!node)
		throw exception("Ошибка! Искомый узел не был найден!");

	return node->data;
}

template <class Key, class Data>
bool Tree<Key, Data>::set(Key key, Data data) {
	Node* node = getNode(key);

	if (!node)
		return false;

	node->data = data;
	return true;
}

template <class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::min(Node* node) {
	if (!node)
		return nullptr;
	if (node->left) {
		Tree<Key, Data>::incrementCOUNTER();
		node = min(node->left);
	}
	return node;
}

template <class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::max(Node* node) {
	if (!node)
		return nullptr;
	if (node->right) {
		Tree<Key, Data>::incrementCOUNTER();
		node = max(node->right);
	}
	return node;
}

template <class Key, class Data>
void Tree<Key, Data>::print() {
	print(root, 0);
}

template <class Key, class Data>
void Tree<Key, Data>::print(Node* node, int lvl) {
	if (!node) {
		for (int i = 0; i < lvl; i++)
			cout << "	";
		cout << "*" << endl;
		return;
	}

	print(node->right, lvl + 1);
	for (int i = 0; i < lvl; i++)
		cout << "	";
	cout << node->key << "(" << node->data << ")" << endl;
	print(node->left, lvl + 1);
}

template <class Key, class Data>
void Tree<Key, Data>::print(Node* node, int lvl, Iterator& iter) {
	if (!node) {
		for (int i = 0; i < lvl; i++)
			cout << "	";
		cout << "*" << endl;
		return;
	}

	print(node->right, lvl + 1, iter);
	for (int i = 0; i < lvl; i++)
		cout << "	";
	if (iter != end() && iter == node)
		cout << "->";
	cout << node->key << "(" << node->data << ")" << endl;
	print(node->left, lvl + 1, iter);
}

template <class Key, class Data>
void Tree<Key, Data>::print(Node* node, int lvl, rIterator& riter) {
	if (!node) {
		for (int i = 0; i < lvl; i++)
			cout << "	";
		cout << "->" << endl;
		return;
	}

	print(node->right, lvl + 1, riter);
	for (int i = 0; i < lvl; i++)
		cout << "	";
	if (riter != rend() && riter == node)
		cout << "*";
	cout << node->key << "(" << node->data << ")" << endl;
	print(node->left, lvl + 1, riter);
}

template <class Key, class Data>
void Tree<Key, Data>::printKeys() {
	printKeys(root);
}

template <class Key, class Data>
void Tree<Key, Data>::printKeys(Node* node) {
	if (!node)
		return;

	Tree<Key, Data>::incrementCOUNTER();

	if (node->left)
		printKeys(node->left);
	cout << node->key << " ";
	if (node->right)
		printKeys(node->right);
}

template <class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::lesserParent(Node* current, Node* target) {
	if (current == target)
		return nullptr;

	Tree<Key, Data>::incrementCOUNTER();
	if (target->key < current->key) {
		Node* node = lesserParent(current->left, target);
		if (!node)
			return current;
		else
			return node;
	}
	else {
		return lesserParent(current->right, target);
	}
}

template <class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::biggerParent(Node* current, Node* target) {
	if (current == target)
		return nullptr;

	Tree<Key, Data>::incrementCOUNTER();
	if (target->key > current->key) {
		Node* node = biggerParent(current->right, target);
		if (!node)
			return current;
		else
			return node;
	}
	else {
		return biggerParent(current->left, target);
	}
}

template <class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::getNext(Node* node) {
	if (isEmpty() || !node)
		throw exception("Ошибка! Узел был nullptr или дерево пусто");

	if (node->right)
		return min(node->right);
	else
		return lesserParent(root, node);
}

template <class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::getPrev(Node* node) {
	if (isEmpty() || !node)
		throw exception("Ошибка! Узел был nullptr или дерево пусто");

	if (node->left)
		return max(node->left);
	else
		return biggerParent(root, node);
}

template <class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::rotateLeft(Node* oldRoot) {
	if (!oldRoot)
		return oldRoot;
	Node* newRoot = oldRoot->right;
	oldRoot->right = newRoot->left;
	newRoot->left = oldRoot;
	root = newRoot;
	return newRoot;
}

template <class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::rotateRight(Node* oldRoot) {
	if (!oldRoot)
		return oldRoot;
	Node* newRoot = oldRoot->left;
	oldRoot->left = newRoot->right;
	newRoot->right = oldRoot;
	root = newRoot;
	return newRoot;
}

template <class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::insertRoot(Key key, Data data, bool& success) {
	success = false;

	insertRoot(key, data, root, success);

	return nullptr;
}

template <class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::insertRoot(Key key, Data data, Node* node, bool& success) {
	if (!node) {
		success = true;
		node = new Node(key, data);
		if (!root)
			root = node;
		size++;
		return node;
	}

	Tree<Key, Data>::incrementCOUNTER();
	if (key == node->key)
		throw exception("Узел с заданным ключом уже существует!");
	if (key < node->key) {
		node->left = insertRoot(key, data, node->left, success);
		return rotateRight(node);
	}
	else {
		node->right = insertRoot(key, data, node->right, success);
		return rotateLeft(node);
	}
}


template <class Key, class Data>
typename Tree<Key, Data>::Iterator Tree<Key, Data>::begin() {
	return Tree<Key, Data>::Iterator(this, min(this->root));
}

template <class Key, class Data>
typename Tree<Key, Data>::Iterator Tree<Key, Data>::end() {
	return Tree<Key, Data>::Iterator(this);
}

template <class Key, class Data>
typename Tree<Key, Data>::rIterator Tree<Key, Data>::rbegin() {
	return Tree<Key, Data>::rIterator(this, max(this->root));
}

template <class Key, class Data>
typename Tree<Key, Data>::rIterator Tree<Key, Data>::rend() {
	return Tree<Key, Data>::rIterator(this);
}

//-----------------Iterator-------------------//

template <class Key, class Data>
bool Tree<Key, Data>::Iterator::operator++(int) {
	if (!node)
		return false;

	node = tree->getNext(node);
	return node;
}

template <class Key, class Data>
bool Tree<Key, Data>::Iterator::operator--(int) {
	if (!node)
		return false;

	node = tree->getPrev(node);
	return node;
}

template <class Key, class Data>
bool Tree<Key, Data>::Iterator::operator==(Iterator it) {
	return node == it.node;
}

template <class Key, class Data>
bool Tree<Key, Data>::Iterator::operator!=(Iterator it) {
	return node != it.node;
}

template <class Key, class Data>
Data& Tree<Key, Data>::Iterator::operator*() {
	if (!node)
		throw exception("Ошибка при работе с итератором!");

	return node->data;
}

template <class Key, class Data>
bool Tree<Key, Data>::Iterator::operator==(Node* node) {
	return this->node == node;
}

//-----------------rIterator------------------//

template <class Key, class Data>
bool Tree<Key, Data>::rIterator::operator++(int) {
	if (!node)
		return false;

	node = tree->getPrev(node);
	return node;
}

template <class Key, class Data>
bool Tree<Key, Data>::rIterator::operator--(int) {
	if (!node)
		return false;

	node = tree->getNext(node);
	return node;
}

template <class Key, class Data>
bool Tree<Key, Data>::rIterator::operator==(rIterator rit) {
	return node == rit.node;
}

template <class Key, class Data>
bool Tree<Key, Data>::rIterator::operator!=(rIterator rit) {
	return node != rit.node;
}

template <class Key, class Data>
Data& Tree<Key, Data>::rIterator::operator*() {
	if (!node)
		throw exception("Ошибка при работе с итератором!");

	return node->data;
}

template <class Key, class Data>
bool Tree<Key, Data>::rIterator::operator==(Node* node) {
	return this->node == node;
}
