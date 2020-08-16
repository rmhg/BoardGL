#pragma once
#include <cstdlib>
#define LineTime(x) auto Start = std::chrono::high_resolution_clock::now();x; auto Duration = std::chrono::high_resolution_clock::now() - Start;std::cout << "Time Taken : " << Duration.count() / 1000000.0f << "ms\n"; 
#define loop(it,x) for(unsigned int i = 0; i < it;i++){x;}


void timeCall(unsigned int n, void(*callback)()) {
	while (n--) {
		callback();
	}
}
void initRandom() {
	srand((unsigned int)time(0));
}
int rand(int low, int high) {
	
	int randv = rand() % high + low;
	return randv;
}

int exrand(int low, int high, int ex) {
	
	int randv = rand() % high + low;
	if (randv == ex)
		return exrand(low, high, ex);
	return randv;
}
float randf(float low, float high) {
	
	float randv = (float)rand(low * 1000, high * 1000)/1000.0f;
	return randv;
}

float reMapfi(int val, int min, int max,int mid = 0, float fmin = -1.0f, float fmax = 1.0f) {
	float fcalc = 0.0f;
	if (val > mid)
		fcalc = (float) val / max;
	else 
		fcalc = (float) val / min;
	return fcalc;
}


template <typename type>
void del(unsigned int index, unsigned int offset, std::vector<type>& vb) {
	unsigned int size = vb.size();
	if (index + offset > size) {
		std::cout << index << " Is Out Of Bounds!" << " | Size : " << size << LF;
		return;
	}
	std::cout << "This " << vb[index] << " Value At " << index << " Going To Be Deleted!\n";
	for (unsigned int i = index; i < vb.size(); i++) {
		if (i + offset >= vb.size())
			break;
		vb[i] = vb[i + offset];
	}
	vb.resize(vb.size() - offset);
}

struct TimeObject {
	std::chrono::steady_clock::time_point Start;
	std::chrono::steady_clock::time_point End;
	std::chrono::nanoseconds Duration;
	TimeObject() {
		Start = std::chrono::high_resolution_clock::now();

	}
	void CalcDuration() {
		End = std::chrono::high_resolution_clock::now();
		Duration = End - Start;
	}
	double Curr() {
		return (std::chrono::high_resolution_clock::now() - Start).count() / 1000000 ;
	}
	~TimeObject() {
	   End  = std::chrono::high_resolution_clock::now();
	   Duration = End - Start;
	   std::cout << "Object Time Last For : " << Duration.count() / 1000000 << "ms\n";
	}
};


template <typename type>
type max(type a1, type a2) {
	return a1 * (a1 >= a2) + a2 * (a1 < a2);
}
template <typename type>
type max(type a1, type a2, type a3) {
	return max(a3, max(a1, a2));
}
template <typename type>
type min(type a1, type a2) {
	return a1 * (a1 <= a2) + a2 * (a1 > a2);
}
template <typename type>
type min(type a1, type a2, type a3) {
	return min(a3, min(a1, a2));
}


template <typename type>
type randP(type* set, type pitem, float probablity) {
	return type();
}

