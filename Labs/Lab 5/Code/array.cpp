/*
* =======================================================
*
* Filename: array.cpp
* Assignment: Lab 5
* Title: Random array generator and sorter
*
* Author: M.Brodskiy & D.Powers
* =======================================================
*/

#include <iostream>
#include <cstdlib>

using namespace std;

void SortArray(int v[], int size) {

	int smallest_index;

	for (int i = 0; i < size; i++) {

		smallest_index = i;

		for (int j = i + 1; j < size; j++) {
	
			if (v[j] < v[smallest_index]) smallest_index = j;

		}
	
		swap(v[i], v[smallest_index]);
		
	}

}

void RandomArray(int v[], int size) {

	for (int i = 0; i < size; i++) {
	
		v[i] = rand() % 100;

	}	

}

void PrintArray(int v[], int size) {

	for (int i = 0; i < size; i++) {

		cout << v[i] << " ";

	}

	cout << endl;

}

int main() {

	int v[10];

	RandomArray(v, 10);
    PrintArray(v, 10);
	SortArray(v, 10);
	PrintArray(v, 10);

	return 0;

}
