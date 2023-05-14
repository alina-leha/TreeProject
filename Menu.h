#pragma once
#include <iostream>
#include "Tree.h"
#include "Test.h"

using namespace std;

typedef int selectKey;
typedef int selectData;

template <class Key = int, class Data = int>
class Menu {
private:
	static void printMainMenu() {
		cout << "���� ���������:" << endl
			<< "[1]	������ ������ ������" << endl
			<< "[2]	�������� ������" << endl
			<< "[3]	��������� ������ �� �������" << endl
			<< "[4]	��������� �������� �� �����" << endl
			<< "[5]	�������� �������� �� �����" << endl
			<< "[6]	��������� ������ �� �����" << endl
			<< "[7]	�������� ������ �� �����" << endl
			<< "[8]	������������ ������ ������ � ������ � ������� L-t-R" << endl
			<< "[9]	������� � ������ ������ �������� � ������, ������� ��������� ��������" << endl
			<< "[10]	����� ������" << endl
			<< "[11]	�������� ������ �������� � ��������� ������� (begin)" << endl
			<< "[12]	�������� ������ �������� � �������� ������� (end)" << endl
			<< "[13]	�������� �������� �������� � ��������� ������� (rbegin)" << endl
			<< "[14]	�������� �������� �������� � �������� ������� (rend)" << endl
			<< "[15]	Iterator == begin()" << endl
			<< "[16]	Iterator == end()" << endl
			<< "[17]	rIterator == rbegin()" << endl
			<< "[18]	rIterator == rend()" << endl
			<< "[19]	Iterator == rIterator" << endl
			<< "[20]	����� �����������" << endl
			<< "[0]	�����" << endl
			<< endl << ">>> ";
	}

	static void printIteratorMenu(bool l) {
		if (l == true)
			cout << "���� ������� ���������:" << endl;
		else
			cout << "���� ��������� ���������:" << endl;

		cout << "[1] ���������" << endl
			<< "[2] ����������" << endl
			<< "[3] �������� ������� ��������" << endl
			<< "[4] �������� ������� ��������" << endl
			<< "[0] �����" << endl
			<< endl << ">>> ";
	}

	static void iteratorMenu(Tree<Key, Data>& tree, typename Tree<Key, Data>::Iterator& iter) {
		int input;
		bool exit = false;
		while (!exit) {
			system("cls");

			tree.print(tree.getRoot(), 0, iter);

			printIteratorMenu(true);
			cin >> input;

			try {
				switch (input) {
				case 1: {
					iter++;
					system("pause");
					break;
				}

				case 2: {
					iter--;
					system("pause");
					break;
				}

				case 3: {
					cout << "������� ��������: " << *iter << endl;
					system("pause");
					break;
				}

				case 4: {
					selectData data;
					cout << "������� ������: " << *iter << endl;
					cout << "����� ������: ";
					cin >> data;
					*iter = data;
					system("pause");
					break;
				}

				case 0: { exit = true; break; }
				default: {
					cout << ">>> ������ �����!\n>>> ";
					system("pause");
					break;
				}
				}
			}

			catch (exception& err) {
				cerr << err.what() << endl;
				system("pause");
			}
			catch (...) {
				cout << ">>> �������������� ������ � ���� ���������!" << endl;
				system("pause");
			}
		}
	}

	static void riteratorMenu(Tree<Key, Data>& tree, typename Tree<Key, Data>::rIterator& riter) {
		int input;
		bool exit = false;
		while (!exit) {
			system("cls");

			tree.print(tree.getRoot(), 0, riter);

			printIteratorMenu(false);
			cin >> input;

			try {
				switch (input) {
				case 1: {
					riter++;
					system("pause");
					break;
				}

				case 2: {
					riter--;
					system("pause");
					break;
				}

				case 3: {
					cout << "������� ��������: " << *riter << endl;
					system("pause");
					break;
				}

				case 4: {
					selectData data;
					cout << "������� ������: " << *riter << endl;
					cout << "����� ������: ";
					cin >> data;
					*riter = data;
					system("pause");
					break;
				}

				case 0: { exit = true; break; }
				default: {
					cout << ">>> ������ �����!\n>>> ";
					system("pause");
					break;
				}
				}
			}

			catch (exception& err) {
				cerr << err.what() << endl;
				system("pause");
			}
			catch (...) {
				cout << ">>> �������������� ������ � ���� ���������!" << endl;
				system("pause");
			}
		}
	}

public:
	static void startMenu(Tree<Key, Data>& tree) {
		auto iter = tree.begin();
		auto riter = tree.rbegin();

		int input;
		bool exit = false;
		while (!exit) {
			system("cls");

			cout << "������ ���������: " << endl;
			if (tree.getSize() == 0)
				cout << "�����";
			else
				tree.print();

			cout << endl << "������ ������: " << tree.getSize() << endl << endl;
			printMainMenu();
			cin >> input;

			try {
				switch (input) {
				case 1: {
					cout << "������ ������: " << tree.getSize() << endl;
					system("pause");
					break;
				}

				case 2: {
					tree.clear();
					cout << "������ �������!" << endl;
					system("pause");
					break;
				}

				case 3: {
					cout << "�������� �� �������" << endl << "������ ��������: " << tree.isEmpty() << endl;
					system("pause");
					break;
				}

				case 4: {
					selectKey key;
					cout << "������ �� �����" << endl;
					cout << "������� ����: ";
					cin >> key;
					Tree<Key, Data>::resetCOUNTER();
					cout << "���������: " << tree.find(key) << endl;
					system("pause");
					break;
				}

				case 5: {
					selectKey key;
					selectData data;
					cout << "��������� �� �����" << endl;
					cout << "������� ����: ";
					cin >> key;
					cout << "������� ������: ";
					cin >> data;
					Tree<Key, Data>::resetCOUNTER();
					cout << "������ ��������: " << tree.set(key, data) << endl;
					system("pause");
					break;
				}

				case 6: {
					selectKey key;
					selectData data;
					cout << "��������� �� �����" << endl;
					cout << "������� ����: ";
					cin >> key;
					cout << "������� ������: ";
					cin >> data;
					Tree<Key, Data>::resetCOUNTER();
					cout << "������ ��������: " << tree.insert(key, data) << endl;
					system("pause");
					break;
				}

				case 7: {
					selectKey key;
					cout << "�������� �� �����" << endl;
					cout << "������� ����: ";
					cin >> key;
					Tree<Key, Data>::resetCOUNTER();
					cout << "������ ��������: " << tree.remove(key) << endl;
					system("pause");
					break;
				}

				case 8: {
					cout << "����������� ������ ������ � ������ � ������� t-L-R" << endl;
					Tree<Key, Data>::resetCOUNTER();
					cout << "�����, ����� ������: "; tree.printKeys(); cout << endl;
					system("pause");
					break;
				}

				case 9: {
					selectKey key;
					selectData data;
					cout << "������� � ������ ������ �������� � ������, ������� ��������� ��������" << endl;
					cout << "������� ����: ";
					cin >> key;
					cout << "������� ������: ";
					cin >> data;
					bool flag;
					tree.insertRoot(key, data, flag);
					cout << "���������: " << flag << endl;
					system("pause");
					break;
				}

				case 10: {
					cout << "����� ������" << endl;
					tree.print();
					cout << endl;
					system("pause");
					break;
				}

				case 11: {
					iter = tree.begin();
					Menu::iteratorMenu(tree, iter);
					break;
				}

				case 12: {
					iter = tree.end();
					Menu::iteratorMenu(tree, iter);
					break;
				}

				case 13: {
					riter = tree.rbegin();
					Menu::riteratorMenu(tree, riter);
					break;
				}

				case 14: {
					riter = tree.rend();
					Menu::riteratorMenu(tree, riter);
					break;
				}

				case 15: {
					cout << "Iterator == begin()" << endl;
					cout << "���������: " << (iter == tree.begin()) << endl;
					system("pause");
					break;
				}

				case 16: {
					cout << "Iterator == end()" << endl;
					cout << "���������: " << (iter == tree.end()) << endl;
					system("pause");
					break;
				}

				case 17: {
					cout << "rIterator == rbegin()" << endl;
					cout << "���������: " << (riter == tree.rbegin()) << endl;
					system("pause");
					break;
				}

				case 18: {
					cout << "rIterator == rend()" << endl;
					cout << "���������: " << (riter == tree.rend()) << endl;
					system("pause");
					break;
				}

				case 19: {
					cout << "Iterator == rIterator" << endl;
					cout << "���������: " << (*iter == *riter) << endl;
					system("pause");
					break;
				}

				case 20: {
					system("cls");

					for (int i = 500, j = 1; i <= 2500; i += 500, j++) {
						cout << "�������� �" << j << "" << endl;
						cout << "���� ����������� �������� ���������� BST-������:" << endl;
						test_rand(i);

						cout << endl << "���� ����������� �������� ������������ BST-������:" << endl;
						test_ord(i);

						cout << endl << "-----------------" << endl << endl;
					}

					system("pause");
					break;
				}

				case 0: { exit = true; break; }
				default: {
					cout << ">>> ������ �����!\n>>> ";
					system("pause");
					break;
				}
				}
			}

			catch (exception& err) {
				cerr << err.what() << endl;
				system("pause");
			}
			catch (...) {
				cout << ">>> �������������� ������ � ������� ����!" << endl;
				system("pause");
			}
		}
	}
};
