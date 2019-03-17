#include <iostream>
#include <stdlib.h>   
#include <time.h>
#include <vector>
#include <windows.h>
#include <time.h>

#include "Crypto_LCG.h"

using namespace std;

int main() {

	setlocale(LC_ALL, "polish");

	Crypto_LCG crypto;

	vector<int>LCG_tab; 

	vector<int>Predict_LCG; 
	vector<int>Predict_LCG_c;
	vector<int>Predict_LCG_a_c;
	vector<int>Predict_LCG_a_c_m;

	int LCG_tab_size;
	int Predict_LCG_size;

	int a_variable;// wspó³czynnik kierunkowy funkcji
	int c_variable; // offset
	int m_variable; // modulo liczby

	int seed;
	int random;
	int first_value;

	time_t time_seed;; 
	seed = time(&time_seed);
	srand(seed);
	first_value = (int)rand() / (RAND_MAX + 1.0) * 100;

	int i,k=0;
	int iteration = 0;

	bool if_the_same = false;


	for (i = 0; i > 10; i++) { 
		LCG_tab[i+1] = 0; 
		Predict_LCG[i] = 0;
		Predict_LCG_c[i] = 0;
		Predict_LCG_a_c[i] = 0;
		Predict_LCG_a_c_m[i] = 0;
	}

	cout << "Kryptografia lista 1" << endl;
	cout << "Zad 1" << endl;
	cout << "Podaj a - wspó³czynnik kierunkowy funkcji: ";
	cin >> a_variable;
	cout << "Podaj wartoœæ offsetu c: ";
	cin >> c_variable;
	cout << "Podaj wartoœæ modulo m: ";
	cin >> m_variable;

	while (if_the_same != true) { // zmieniæ warunek w pêtli na taki który umo¿liwi wyjœcie po osi¹gniêciu wyniku ¿e LCG = broke LCG
		random = (int)rand() / (RAND_MAX + 1.0) * 100;
		if (k == 0) {

			LCG_tab.push_back(crypto.LCG(random, a_variable, c_variable, m_variable));
			cout << "Wartoœæ LCG: " << LCG_tab[k] << endl;

			Predict_LCG.push_back(crypto.Distinguisher_LCG_all(random, a_variable, c_variable, m_variable));
			cout << "Wartoœæ przewidywana przez adwersarza - wszytsko znane: " << Predict_LCG[k] << endl;

		}
		else {

			LCG_tab.push_back(crypto.LCG(LCG_tab[k-1], a_variable, c_variable, m_variable));
			cout << "Wartoœæ LCG: " << LCG_tab[k] << endl;

			Predict_LCG.push_back(crypto.Distinguisher_LCG_all(LCG_tab[k-1], a_variable, c_variable, m_variable));
			cout << "Wartoœæ przewidywana przez adwersarza - wszytsko znane: " << Predict_LCG[k] << endl;


			if (k > 1) {
				Predict_LCG_c.push_back(crypto.Distinguisher_LCG_unknown_c(LCG_tab[k-2], LCG_tab[k-1], m_variable, a_variable));
				cout << "Wartoœæ przewidywana przez adwersarza - nieznane c: " << Predict_LCG_c[k-2] << endl;
			}
			
			if (k > 2) {
				Predict_LCG_a_c.push_back(crypto.Distinguisher_LCG_unknown_a_c(LCG_tab[k - 3], LCG_tab[k - 2], LCG_tab[k-1], m_variable));
				cout << "wartoœæ przewidywana przez adwersarza - nieznane a,c: " << Predict_LCG_a_c[k-3] << endl;
			}

			//Predict_LCG_a_c_m.push_back(crypto.Distinguisher_LCG_unknown_a_c_m(LCG_tab[]))
		}
			
		system("PAUSE");
		//Sleep(1000);//zatrzymanie procesu by przeczytaæ liczbê
		//	if (LCG_tab[k] == Predict_LCG[k]){// && LCG_tab[k] == Predict_LCG_m[k]) {
		//		if_the_same = true;
		//		cout << "Wartoœci s¹ takie same!" << endl;
		//	}
		//else
			if_the_same = false;
		k++;
	}
	
	if_the_same = false;
	system("PAUSE");
	return (0);
}