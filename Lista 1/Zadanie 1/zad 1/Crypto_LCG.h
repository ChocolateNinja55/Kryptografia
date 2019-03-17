#pragma once
#include <vector>
class Crypto_LCG
{
public:
	Crypto_LCG();
	~Crypto_LCG();

	int x; // z strony tailcall.net

	int LCG(int x, int a, int c, int m);

	int Distinguisher_LCG_all(int x, int a, int c, int m); // mamy wszytko
	int Distinguisher_LCG_unknown_c(int x, int y, int m, int a);
	int Distinguisher_LCG_unknown_a_c(int x, int y, int z, int m);
	int Distinguisher_LCG_all_unknown(int *tab);

	int modinv(int elements, int modulus);
};

