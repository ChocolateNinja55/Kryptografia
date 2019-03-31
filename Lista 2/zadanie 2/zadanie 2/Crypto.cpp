#include "Crypto.h"

#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>

Crypto::Crypto()
{
	time_t time_seed;
	int seed = time(&time_seed);
	srand(seed);
}

Crypto::~Crypto()
{}

std::vector<int>Crypto::KSA(int N_variable, int T_variable, std::vector<int>key) {
	int j, i = 0;
	int lenght_key;

	std::vector<int>S_value;
	std::vector<int>return_value;
	lenght_key = key.size();

	for  (i = 0; i < N_variable - 1; i++) 
		S_value.push_back(i);

	for (i = 0; i < T_variable; i++) {
		j = (j + S_value[i % N_variable] + key[i % lenght_key]) % N_variable; 
		std::swap(S_value[i % N_variable], S_value[j % N_variable]);
	}
	return_value = S_value;
	return return_value;
}

std::vector<int>Crypto::PRGA(int N_variable, std::vector<int>S_value) {
	std::vector<int>return_value;
	std::vector<int>S_value;
	int i, j = 0;
	
	while () {//???
		i = (i + 1) % N_variable;
		j = (j + S_value[i]) % N_variable;
		std::swap(S_value[i], S_value[j]);
		S_value.push_back(S_value[(S_value[i] + S_value[j]) % N_variable]);
	}

	return_value = S_value;
	return return_value;
}

std::vector<int>Crypto::KSA_RS(int N_variable, int T_variable, std::vector<int>key) {
	std::vector<int>return_value;
	std::vector<int>newS_value;
	std::vector<int>S_value;
	std::vector<int>Top;
	std::vector<int>Bottom;

	int key_lenght = S_value.size();

	for (int i = 0; i < N_variable - 1; i++) 
		S_value.push_back(i);
	
	for (int j = 0; j < T_variable; j++) {
		for (int k = 0; k < N_variable; k++) {
			if (key[j * N_variable + k % key_lenght] == 0)
				Top.push_back(j);
			else
				Bottom.push_back(j);
		}
	}
	for (int m = 0; m < Top.size(); m++) 
		newS_value.push_back(S_value[m]);
	
	for (int u = 0; u < Bottom.size(); u++) 
		newS_value.push_back(Top.size() + u);
	
	return_value = newS_value;
	return return_value;
}

std::vector<int>Crypto::Generate_key(int sizeof_key, int seed){
	std::vector<int>return_value;
	std::vector<int>temp_value;

	for (int i = 0; i < sizeof_key; i++) 
		temp_value.push_back((int)rand() / (RAND_MAX + 1.0) * 1);
	
	return_value = temp_value;
	return return_value;
}

std::vector<int>Crypto::RC4(int N_variable, int T_variable, std::vector<int>key) {
	std::vector<int>temp;

	temp = KSA(N_variable, T_variable, key);
	return PRGA(N_variable, temp);
}

std::vector<int>Crypto::RC4_RS(int N_variable, int T_variable, std::vector<int>key) {
	std::vector<int>temp;
	int new_T = 2 * T_variable *log(N_variable);

	temp = KSA_RS(N_variable, new_T, key);
	return PRGA(N_variable, temp);
}
//do zrobienia
std::vector<int>Crypto::RC4_SST(int N_variable, int T_variable, std::vector<int>key) { // do zrobienia

}

std::vector<int>Crypto::RC4_with_drop(int N_variable, int T_variable, int D_value, std::vector<int>key) {
	std::vector<int>temp;
	std::vector<int>return_value;
	temp = RC4(N_variable, T_variable, key);

	return return_value;
}
std::vector<int>Crypto::RC4_RS_with_drop(int N_variable, int T_variable, int D_value, std::vector<int>key) {}
std::vector<int>Crypto::RC4_SST_with_drop(int N_variable, int T_variable, int D_value, std::vector<int>key) {}

void Safe_to_file(std::string name, std::vector<int>data) {
	std::ofstream file;
	file.open(name, std::ios::out);
	if (file.is_open()) {
		for (int m = 0; m < data.size(); m++) {
			file << data[m] << std::endl;
		}
	}
	file.close();
}

std::vector<int>Return_drop(int D_drop, std::vector<int>data) {
	return
}