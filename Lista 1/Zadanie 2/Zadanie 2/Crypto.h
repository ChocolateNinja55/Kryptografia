#pragma once
#include <vector>
class Crypto
{
public:
	std::vector<int>tab;
	std::vector<int>predict;

	Crypto();
	~Crypto();
	
	void glibc();
	void init(int seed, int tab_size);
	void predict_glbc(int start_frame, int end_frame);
};

