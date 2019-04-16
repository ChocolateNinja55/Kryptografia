#include "Crypto.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h> 
#include <iostream>
#include <string>

using namespace std;

int main() {
	int array_size;
	int key_lenght;
	int drop_D;
	int random;
	int temp;
	int how_many_probe = 10000;
	int how_many_probe_RC4_RS = 10000;
	string name1;
	string name2;
	string name3;
	string name4;

	time_t time_seed;
	int seed = time(&time_seed);
	srand(seed);

	vector<int>key;
	vector<int>RC4;
	vector<int>RC4_RS;

	vector<int>RC4_mdrop;
	vector<int>RC4_RS_mdrop;

	random = rand() % 999999 + 1;
	Crypto crypto;

	setlocale(LC_ALL, "polish");

	cout << "Kryptografia Lista 2\nzadanie 2" << endl;
	cout << "Podaj N (jedno z: 16, 64, 256): ";
	cin >> array_size;
	cout << "Podaj d³ugoœæ klucza (jedno z: 40, 64, 128): ";
	cin >> key_lenght;
	cout << "Podaj wartoœæ dropu D (jedno z: 0, 1, 2, 3): ";
	cin >> drop_D;

	name1 = "RC4-N" +  to_string(array_size) + "-k" + to_string(key_lenght) +".txt";
	name2 = "RC4_mdrop_N" + to_string(array_size) + "k" + to_string(key_lenght) + "-Drop" + to_string(drop_D) + ".txt";
	name3 = "RC4_RS-N" + to_string(array_size) + "k" + to_string(key_lenght) + ".txt";
	name4 = "RC4_RS_mdrop-N" + to_string(array_size) + "k" + to_string(key_lenght) + "-Drop" + to_string(drop_D) + ".txt";

	key = crypto.Generate_key(key_lenght, random);
	//RC4 = crypto.RC4(array_size, array_size, key,how_many_probe);
	RC4_RS = crypto.RC4_RS(array_size, array_size, key, how_many_probe_RC4_RS);

	//RC4_mdrop = crypto.RC4_with_drop(array_size, array_size, drop_D, key,how_many_probe);
	RC4_RS_mdrop = crypto.RC4_RS_with_drop(array_size, array_size, drop_D, key, how_many_probe_RC4_RS);

	//crypto.Safe_to_file(name1, RC4_mdrop);
	//crypto.Safe_to_file(name2, RC4);
	crypto.Safe_to_file(name3, RC4_RS_mdrop);
	crypto.Safe_to_file(name4, RC4_RS);

	system("PAUSE");

	return 0;
}