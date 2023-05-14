#pragma once
#include <ctime>
#include <cmath>
#include <iostream>
#include "Tree.h"
using namespace std;

typedef unsigned long long INT_64;
//���������� � ��������� ���������� LineRand()
static INT_64 RRand = 15750;
const INT_64 mRand = (1 << 63) - 1;
const INT_64 aRand = 6364136223846793005;
const INT_64 cRand = 1442695040888963407;

//������� ��������� ������� ���������� ����� �� ����� ����������
void sRand() {
    srand(time(0));
    RRand = (INT_64)rand();
}
//������� ��������� ���������� �����

//�������� ������������ ��������� Xi+1=(a*Xi+c)%m

INT_64 LineRand() {
    INT_64 y1, y2;
    y1 = (aRand * RRand + cRand) % mRand;
    y2 = (aRand * y1 + cRand) % mRand;
    RRand = y1 & 0xFFFFFFFF00000000LL ^ (y2 & 0xFFFFFFFF00000000LL) >> 32;
    return RRand;
}

void test_rand(int n) {
    //�������� ������ ��� 64 � ��������� ������ ���� INT_64
    Tree<INT_64, int> tree;
    //������ ��� ������, ������� ������������ � ������
    INT_64* m = new INT_64[n];
    //��������� ������� ���������� �����
    sRand();
    //���������� ������ � ������� ���������� �� ���������� �������
    for (int i = 0; i < n; i++) {
        m[i] = LineRand();
        tree.insert(m[i], 1);
    }
    //����� ������� ������ �� �����
    cout << "items count: " << tree.getSize() << endl;
    //��������� ��������� ����������� �������, �������� � ������
    double I = 0;
    double D = 0;
    double S = 0;
    //��������� ������ ��������, 10% - ������� ��������
    for (int i = 0; i < n / 2; i++)
        if (i % 10 == 0) //10% ��������
        {
            Tree<INT_64, int>::resetCOUNTER();
            tree.remove(LineRand());
            D += Tree<INT_64, int>::getCOUNTER();
            Tree<INT_64, int>::resetCOUNTER();
            tree.insert(m[rand() % n], 1);
            I += Tree<INT_64, int>::getCOUNTER();
            try {
                Tree<INT_64, int>::resetCOUNTER();
                tree.find(LineRand());
                S += Tree<INT_64, int>::getCOUNTER();
            }
            catch (const exception& e) {
                S += Tree<INT_64, int>::getCOUNTER();
            }
        }
        else //90% �������� ��������
        {
            int ind = rand() % n;
            Tree<INT_64, int>::resetCOUNTER();
            tree.remove(m[ind]);
            D += Tree<INT_64, int>::getCOUNTER();
            INT_64 key = LineRand();
            Tree<INT_64, int>::resetCOUNTER();
            tree.insert(key, 1);
            I += Tree<INT_64, int>::getCOUNTER();
            m[ind] = key;
            try {
                Tree<INT_64, int>::resetCOUNTER();
                tree.find(m[rand() % n]);
                S += Tree<INT_64, int>::getCOUNTER();
            }
            catch (const exception& e) {
                S += Tree<INT_64, int>::getCOUNTER();
            }
        }
    cout << "items count: " << tree.getSize() << endl;
    //������������� ������ ����������� �������� BST
    cout << "1.39*log2(n)= " << 1.39 * (log((double)n) / log(2.0)) << endl;
    //����������������� ������ ����������� �������
    cout << "Count insert: " << I / (n / 2) << endl;
    //����������������� ������ ����������� ��������
    cout << "Count delete: " << D / (n / 2) << endl;
    //����������������� ������ ����������� ������
    cout << "Count search: " << S / (n / 2) << endl;
    //������������ ������ ������� m[]
    delete[] m;
}

void test_ord(int n) {
    //�������� ������ ��� 64 � ��������� ������ ���� INT_64
    Tree<INT_64, int> tree;
    //������ ��� ������, ������� ������������ � ������
    INT_64* m = new INT_64[n];
    //���������� ������ � ������� ���������� � ������������� ������� //������� �� ��������� [0, 10000, 20000, ... ,10000*n]
    for (int i = 0; i < n; i++) {
        m[i] = i * 10000;
        tree.insert(m[i], 1);
    }
    //����� ������� ������ �� �����
    cout << "items count: " << tree.getSize() << endl;
    //��������� ��������� ����������� �������, �������� � ������
    double I = 0;
    double D = 0;
    double S = 0;
    //��������� ������� ���������� �����
    sRand();
    //��������� ������ ��������, 10% - ������� ��������
    for (int i = 0; i < n / 2; i++) {
        if (i % 10 == 0) //10% ��������
        {
            int k = LineRand() % (10000 * n);
            k = k + !(k % 2); //��������� �������� ����
            Tree<INT_64, int>::resetCOUNTER();
            tree.remove(k);
            D += Tree<INT_64, int>::getCOUNTER();
            Tree<INT_64, int>::resetCOUNTER();
            tree.insert(m[rand() % n], 1);
            I += Tree<INT_64, int>::getCOUNTER();
            k = LineRand() % (10000 * n);
            k = k + !(k % 2); // ��������� �������� ����
            try {
                Tree<INT_64, int>::resetCOUNTER();
                tree.find(k);
                S += Tree<INT_64, int>::getCOUNTER();
            }
            catch (const exception& e) {
                S += Tree<INT_64, int>::getCOUNTER();
            }
        }
        else //90% �������� ��������
        {
            int ind = rand() % n;
            Tree<INT_64, int>::resetCOUNTER();
            tree.remove(m[ind]);
            D += Tree<INT_64, int>::getCOUNTER();
            int k = LineRand() % (10000 * n);
            k = k + k % 2; // ��������� ������ ����
            Tree<INT_64, int>::resetCOUNTER();
            tree.insert(k, 1);
            I += Tree<INT_64, int>::getCOUNTER();
            m[ind] = k;
            try {
                Tree<INT_64, int>::resetCOUNTER();
                tree.find(m[rand() % n]);
                S += Tree<INT_64, int>::getCOUNTER();
            }
            catch (const exception& e) {
                S += Tree<INT_64, int>::getCOUNTER();
            }
        }
    }
    //����� �����������:

    // ����� ������� ������ ����� �����
    cout << "items count: " << tree.getSize() << endl;
    //������������� ������ ����������� �������� BST
    cout << "n/2 = " << n / 2 << endl;
    //����������������� ������ ����������� �������
    cout << "Count insert: " << I / (n / 2) << endl;
    //����������������� ������ ����������� ��������
    cout << "Count delete: " << D / (n / 2) << endl;
    //����������������� ������ ����������� ������
    cout << "Count search: " << S / (n / 2) << endl;
    //������������ ������ ������� m[]
    delete[] m;
}
