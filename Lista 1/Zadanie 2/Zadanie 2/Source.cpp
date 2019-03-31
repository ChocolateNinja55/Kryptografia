#include <iostream>
#include <Windows.h>
#include <vector>

#include "Crypto.h"
using namespace std;

int main() {

	setlocale(LC_ALL, "polish");

	int seed = 1;
	int k = 0;
	int tab_size;
	int i;

	int start_frame = 0;
	int end_frame = 1; // warto�ci pocz�tkowe

	bool is_the_same = false;
	Crypto crypto;

	vector<int>glbic_tab;
	vector<int>predict_glbc_tab;
	

	cout << "Zadanie 2 - kryptografia" << endl;
	cout << "Warto�� ziarna (seed): ";
	cin >> seed;
	cout << "Wielko�� tablicy glbic:";
	cin >> tab_size;
	cout << "Podaj pocz�tek ramki przeszukiwawczej: "; 
	// predict b�dzie polega� na tym i� pobieramy od u�ytkownika granic� ramki szukaj�cej tzn. od 5 do 15 - 
	// czyli pobieramy z tablicy 10 element�w i je analizujemy

	cin >> start_frame;
	cout << "Podaj koniec ramki przeszukiwawczej (min +31): ";
	cin >> end_frame;

	if (start_frame >= end_frame || end_frame == 0 ||end_frame > 10000) { // zabezpieczenia przed u�ytkownikiem
		cout << "Z�e parametry okna - zamykanie aplikacji" << endl;
		Sleep(2000);
		return 0;
	}
	else if (start_frame + 31 > end_frame) {
		cout << "Za ma�a wielko�� okna" << endl;
		Sleep(2000);
		return 0;
	}

	crypto.init(seed, tab_size); // seed
	

	//while (is_the_same != true) {
	
		crypto.glibc(); // mamy w tablicy warto�ci random z algorytmu glbc
	
		crypto.predict_glbc(start_frame,end_frame);
		system("PAUSE");
		crypto.distinguisher(start_frame, end_frame);
		system("PAUSE");
/*
		if (glbic_tab[k] == predict_glbc_tab[k]) {
		
			is_the_same = true;
			cout << "Warto�ci s� takie same!" << endl;
			system("PASUE");
		}
		*/
	//	k++;
	//	is_the_same = false;
	//}
	

	return 0;
}