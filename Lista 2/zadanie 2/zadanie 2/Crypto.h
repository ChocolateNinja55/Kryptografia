#pragma once
#include <vector>
class Crypto
{
public:
	Crypto();
	~Crypto();

	std::vector<int>KSA(int N_variable, int T_variable, std::vector<int>key);
	std::vector<int>PRGA(int N_variable, std::vector<int>data, int how_many);
	std::vector<int>KSA_RS(int N_variable, int T_variable, std::vector<int>key);
	std::vector<int>Generate_key(int sizeof_key, int seed);

	std::vector<int>RC4(int N_variable, int T_variable, std::vector<int>key, int how_many);
	std::vector<int>RC4_RS(int N_variable, int T_variable, std::vector<int>key, int how_many);
	std::vector<int>RC4_SST_end(int N_variable, std::vector<int>key, int how_may);
	std::vector<int>RC4_SST(int N_variable, std::vector<int>key);

	std::vector<int>RC4_with_drop(int N_variable, int T_variable, int D_value, std::vector<int>key, int how_many);
	std::vector<int>RC4_RS_with_drop(int N_variable, int T_variable, int D_value, std::vector<int>key, int how_many);
	std::vector<int>RC4_SST_with_drop(int N_variable, int T_variable, int D_value, std::vector<int>key, int how_many);

	std::vector<int>Return_drop(int D_drop, std::vector<int>data);
	void Safe_to_file(std::string name, std::vector<int>data);
};

