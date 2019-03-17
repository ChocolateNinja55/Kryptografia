#include "Crypto_LCG.h"
#include <iostream>
#include <functional>
#include <vector>

Crypto_LCG::Crypto_LCG(){}
Crypto_LCG::~Crypto_LCG(){}
//https://tailcall.net/blog/cracking-randomness-lcgs/
int Crypto_LCG::LCG(int x, int a, int c, int m) {
	int temp;
	temp = (a * x + c) % m;
	return temp;
}
int Crypto_LCG::Distinguisher_LCG_all(int x, int a, int c, int m) { //mamy wszystko
	int result;
	result = (a * x + c) % m;
	return result;
}
int Crypto_LCG::Distinguisher_LCG_unknown_c(int x, int y, int m, int a) { 
	//c  = s1 - s0*m  (mod n)
	//increment = (states[1] - states[0]*multiplier) % modulus

	int new_c;
	int result;
	int var_1;

	var_1 = (y - x * a);
	new_c = var_1 % m;

	result = Distinguisher_LCG_all(y, a, new_c, m);
	return result;
}
int Crypto_LCG::Distinguisher_LCG_unknown_a_c(int x, int y, int z, int m) { 
	//multiplier = (states[2] - states[1]) * modinv(states[1] - states[0], modulus) % modulus

	int result;
	int temp;
	int	new_a;
	int var_1;

	int var_3 = y - x;
	temp = modinv(var_3, m);
	int var_2 = z - y;
	var_1 = var_2 * temp;
	new_a = std::modulus<int>()(var_1, m);

	result = Distinguisher_LCG_unknown_c(x, y, m, new_a);
	return result;
}
int Crypto_LCG::Distinguisher_LCG_all_unknown(int *tab) {
	int diffrence;
	int zero;
	int modulus;
	int i,j;
	int *temp;

	int size = sizeof(tab) / sizeof(int); // wielkoœæ tablicy
	
	for (i = 0; i < size; i++) { //"alokacja pamiêci"
		temp[i] = 0;
	}

	/*for (j = 0; j < size; j++) {
	
	}*/
}
int *egcd(int elements, int modulus) {
	int *temp = (int *)malloc(sizeof(int) * 3);

	if (modulus == 0){
		temp[0] = elements;
		temp[1] = 1;
		temp[2] = 0;
		return temp;
	}
	else {
		int var1, var2;
		temp = egcd(modulus, elements % modulus);
		var1 = temp[1];
		var2 = temp[2];
		temp[1] = temp[2];
		temp[2] = var1 - elements / modulus * var2;
		return temp;
	}
// from https://en.wikibooks.org/wiki/Algorithm_Implementation/Mathematics/Extended_Euclidean_algorithm
}
int Crypto_LCG::modinv(int elements, int modulus) { //  = element 1 - element 0, b = modulus)

	int *ptr;
	ptr = egcd(elements, modulus);

	if (ptr[0] == 1)
		return ptr[2] % modulus;
}
