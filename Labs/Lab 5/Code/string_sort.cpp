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
#include <string>

using namespace std;

void SortArray(string v[], int size) {

	int smallest_index;

	for (int i = 0; i < size; i++) {

		smallest_index = i;

		for (int j = i + 1; j < size; j++) {
	
			if (v[j] < v[smallest_index]) smallest_index = j;

		}
	
		swap(v[i], v[smallest_index]);
		
	}

}

void ReadArray(string v[], int size) {

	for (int i = 0; i < size; i++) {
	
		cout << "Enter string #" << i << ": ";
		cin >> v[i];

	}	

}

void PrintArray(string v[], int size) {

	for (int i = 0; i < size; i++) {

		cout << v[i] << endl;

	}

}

int main() {

	string v[10];

	ReadArray(v, 10);
	SortArray(v, 10);
	PrintArray(v, 10);

	return 0;

}
