#include "Crypto.h"

#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>

#include <bitset>
#include <functional>
#include <algorithm>
#include <sstream>

Crypto::Crypto(){
	int i, zarodek;
	time_t tt;
	zarodek = time(&tt);
	srand(zarodek);
}

Crypto::~Crypto()
{}

std::vector<int>Crypto::KSA(int N_variable, int T_variable, std::vector<int>key) {
	int j = 0;
	int i = 0;
	int lenght_key;
	std::string cos;

	std::vector<int>S_value;
	std::vector<int>return_value;
	lenght_key = key.size()/8;
	
	//std::string binary = std::bitset<32>(key.size()).to_string();
	//lenght_key = binary.size();

	for  (i = 0; i < N_variable; i++) //N-1
		S_value.push_back(i);

	for (i = 0; i < T_variable; i++) {
		j = (j + S_value[i % N_variable] + key[i % lenght_key]) % N_variable; 
		std::swap(S_value[i % N_variable], S_value[j % N_variable]);
	}
	return_value = S_value;
	return return_value;
}

std::vector<int>Crypto::PRGA(int N_variable, std::vector<int>S_value, int how_many) {
	std::vector<int>return_value;
	int i = 0;
	int j = 0;
	int k = 0;
	
	while (k < how_many) {
		i = (i + 1) % N_variable;
		j = (j + S_value[i]) % N_variable;
		std::swap(S_value[i], S_value[j]);
		S_value.push_back(S_value[(S_value[i] + S_value[j]) % N_variable]);
		k++;
	}

	return_value = S_value;
	return return_value;
}

std::vector<int>Crypto::KSA_RS(int N_variable, int T_variable, std::vector<int>key) {
	std::vector<int>newS_value;
	std::vector<int>S_value;
	std::vector<int>Top;
	std::vector<int>Bottom;

	int key_lenght = key.size();

	for (int i = 0; i < N_variable - 1; i++) 
		S_value.push_back(i);
	
	for (int j = 0; j < T_variable; j++) {
		for (int k = 0; k < N_variable; k++) {
			if (key[(j * N_variable + k ) % key_lenght] == 0)
				Top.push_back(k);
			else
				Bottom.push_back(k);
		}
	}
	for (int m = 0; m < S_value.size(); m++) 
		newS_value.push_back(S_value[m]);
	
	for (int u = 0; u < S_value.size(); u++) 
		newS_value.push_back(S_value[u]);
	
	for (int y = 0; y < S_value.size(); y++) 
		S_value[y] = newS_value[y];
	
	return S_value;
}

std::vector<int>Crypto::Generate_key(int sizeof_key, int seed){
	std::vector<int>return_value;
	std::vector<int>temp_value;

	for (int i = 0; i < sizeof_key*8; i++)
		temp_value.push_back(std::rand() % 2 + 0);
	
	return_value = temp_value;
	return return_value;
}

std::vector<int>Crypto::RC4(int N_variable, int T_variable, std::vector<int>key, int how_many) {
	std::vector<int>temp;

	temp = KSA(N_variable, T_variable, key);
	return PRGA(N_variable, temp, how_many);
}

std::vector<int>Crypto::RC4_RS(int N_variable, int T_variable, std::vector<int>key,int how_many) {
	std::vector<int>temp;
	int new_T = 2 * T_variable *log(N_variable);

	temp = KSA_RS(N_variable, new_T, key);
	return PRGA(N_variable, temp,how_many);
}

//do zrobienia
//std::vector<int>Crypto::RC4_SST(int N_variable, int T_variable, std::vector<int>key) { // do zrobienia}

std::vector<int>Crypto::RC4_with_drop(int N_variable, int T_variable, int D_value, std::vector<int>key, int how_many) {
	std::vector<int>temp;
	std::vector<int>return_value;

	temp = RC4(N_variable, T_variable, key, how_many);

	return return_value = Return_drop(D_value, temp);
}

std::vector<int>Crypto::RC4_RS_with_drop(int N_variable, int T_variable, int D_value, std::vector<int>key, int how_many) {
	std::vector<int>return_data;
	std::vector<int>temp;

	temp = RC4_RS(N_variable, T_variable, key, how_many);

	return return_data = Return_drop(D_value,temp);
}

std::vector<int>Crypto::RC4_SST_with_drop(int N_variable, int T_variable, int D_value, std::vector<int>key, int how_many) {
	std::vector<int>return_drop;
	return return_drop;
}

void Crypto::Safe_to_file(std::string name, std::vector<int>data) {
	std::ofstream file;
	file.open(name, std::ios::out);
	if (file.is_open()) {
		for (int m = 0; m < data.size(); m++) {
			file << std::hex << data[m] << std::endl;
		}
	}
	file.close();
}

std::vector<int>Crypto::Return_drop(int D_drop, std::vector<int>data) {
	int k = 0;
	int iteration;
	int string_to_int = 0;
	char znak = '\0'; // wartoœæ null

	std::vector<int>return_table;
	std::vector<int>temp_data;

	std::string temp;
	std::vector<std::string> temp_table;

	// 1 int to 4 bajty
	for (int i = 0; i < data.size(); i++) {
		std::string binary = std::bitset<32>(data[i]).to_string();

		for (int j = 0; j < binary.size(); j++) {
			if ((k == 8) && (D_drop == 1) ) {
				temp.erase(0, D_drop);
				k = 0;
			}
			else if ((k == D_drop + 1) && (D_drop == 2)) {
				temp.erase(0, D_drop);
				k = 0;
			}
			else if ((k == D_drop + 1) && (D_drop == 3)) {
				temp.erase(0, D_drop);
				k = 0;
			}
			else {
				znak = binary[j];
				temp += znak;
			}
			znak = '\0';
			k++;
		}

		iteration = 0;

		for (int m = temp.size() - 1; m >= 0; m--) {
			if (temp[m] == '1')
				string_to_int += pow(2, iteration);
			iteration++;
		}
		return_table.push_back(string_to_int);
		temp.clear();
		string_to_int = 0;
	}
	return return_table;
}