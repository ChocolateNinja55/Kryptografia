#include "Crypto.h"
#include <iostream>

using namespace std;

int main() {
	int array_size;
	int key_lenght;
	int drop_D;

	Crypto crypto;

	cout << "Kryptografia Lista 2\nzadanie 2" << endl;
	cout << "Podaj N (jedno z: 16,64,246): ";
	cin >> array_size;
	cout << "Podaj d³ugoœæ klucza (jedno z: 40, 64, 128): ";
	cin >> key_lenght;
	cout << "Podaj wartoœæ dropu D (jedno z: 0,1,2,3): ";
	cin >> drop_D;




	return 0;
}