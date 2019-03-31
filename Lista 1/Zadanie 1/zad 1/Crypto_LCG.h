#pragma once
#include <vector>
class Crypto_LCG
{
public:
	Crypto_LCG();
	~Crypto_LCG();

	int x;

	int LCG(int x, int a, int c, int m);

	int Predict_LCG_all(int x, int a, int c, int m);
	int Predict_LCG_unknown_c(int x, int y, int m, int a);
	int Predict_LCG_unknown_a_c(int x, int y, int z, int m);
	int Predict_LCG_all_unknown(std::vector<int>data);

	int modinv(int elements, int modulus);
};

