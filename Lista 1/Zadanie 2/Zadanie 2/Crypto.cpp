#include "Crypto.h"
#include <iostream>
#include <vector>

Crypto::Crypto(){}
Crypto::~Crypto(){}

// ze strony https://www.mathstat.dal.ca/~selinger/random/

void Crypto::glibc() {
	int i;
	long int temp =0;
	long int resoult = 0;

	for (i = 1; i<31; i++) {
		temp = tab[i - 1];
		tab[i] = (16807LL * temp) % 2147483647;
		if (tab[i] < 0) {
			tab[i] += 2147483647;
		}
	}
	for (i = 31; i<34; i++) {
		tab[i] = tab[i - 31];
	}
	for (i = 34; i<344; i++) {
		tab[i] = tab[i - 31] + tab[i - 3];
	}
	for (i = 344; i<1000; i++) {
		tab[i] = tab[i - 31] + tab[i - 3];
	}
}

void Crypto::predict_glbc(int start_frame, int end_frame) {
	int  k = start_frame;
	int i,j;
	bool all_data_read = false;

	int temp_value_1 = 0;
	int temp_value_2 = 0;

	std::vector<int>temp;

	for (i = 0; i < end_frame; i++) {

		if (i >= start_frame) {
			temp.push_back(tab[i]);
		}
		else
			temp.push_back(0);
	}
	std::cout << "Wartoœci poszczególnych wartosci z okna podanego na pocz¹tku zadania" << std::endl;
		
			for (int i = start_frame; i <end_frame; i++) {std::cout << temp[i] << std::endl;}

	if (end_frame < 31) {
			//brak mo¿liwoœci przewidywania - nie mamy elementów [i - 31], [i - 3]
	}
	else if (end_frame >= 31 && end_frame < 34) {
			for ( i = start_frame; i < end_frame; i++) {
				temp_value_1 = temp[i];
				temp_value_2 = temp[i - 31];

				predict.push_back(temp_value_2);
			}
	}
	else if (end_frame >= 34 && end_frame < 344){ 
			for ( i = start_frame; i < end_frame; i++) {
				temp_value_1 = tab[i - 3];
				temp_value_2 = tab[i - 31]; 

				predict.push_back(temp_value_2 + temp_value_1);
			}
	}
	else { // od 344 do limitu // na patêcie ostatnie kilka elementów jest przewidywana 345 - 380

			for (j = start_frame + 31; j < end_frame; j++) {
				temp_value_1 = temp[j - 3];
				temp_value_2 = temp[j - 31];

				predict.push_back(temp_value_2 + temp_value_1);
			}
	}
		for (int m = 0; m < predict.size(); m++) {
			std::cout << "Przewidywana wartoœæ" << std::endl;
			std::cout << predict[m] << std::endl;
		}
}

void Crypto::init(int seed, int tab_size) { // inicjalizacja tablicy pod glbic
	int i;

	for (i = 0; i < tab_size; i++) {
		if (i == 0)
			tab.push_back(seed);
		else
			tab.push_back(0);
	}
}

void Crypto::distinguisher(int start_frame, int end_frame) {
	std::vector<int>predict_value;
	int temp_value1 = 0;
	int temp_value2 = 0;
	int temp_value_3 = 0;

	for (int i = start_frame; i < end_frame; i++) {
		temp_value1 = tab[i - 3];
		temp_value2 = tab[i - 31];
		temp_value_3 = ((temp_value2 + temp_value1) % (1u << 31));
		predict_value.push_back(temp_value_3); // pierwszy bit od lewej strony
	}

	std::cout << "Distinguisher" << std::endl;
	for (int j = 0; j < predict_value.size(); j++) {
		std::cout << predict_value[j] << std::endl;
	}
	compare(tab, predict_value, start_frame, end_frame);
}

void Crypto::compare(std::vector<int>good_data, std::vector<int>maybe_good_data, int start_frame, int end_frame) {
	int how_many = 0;
	int size = maybe_good_data.size();

	for (int i = start_frame; i < end_frame; i++) {
		if (good_data[i] == maybe_good_data[i - start_frame]) {
			std::cout << i << "\t" << good_data[i] << std::endl;
			how_many++;
		}	
	}

	std::cout << "Podobieñstwo: " << how_many/size << std::endl;
}