#pragma once
#ifndef NUMPARSE_H
#define NUMPARSE_H

class NumParse {
public :
	static int Integer(const std::string&);
	static float Float(const std::string&);
	static double Double(const std::string&);
};
int NumParse::Integer(const std::string& num) {
	int a = 0;
	bool neg = false;
	int exp = 0;
	if (num[0] == '-')
		neg = true;
	for (unsigned int i = 0; i < num.size(); i++) {
		char c = num[i];
		if (i > 0 && (c == 'e' || c == 'E')) {
			std::string s = "";
			for (unsigned int j = i + 1; j < num.size(); j++) {
				s += num[j];
			}
			exp = NumParse::Integer(s);
			break;
		}
		if (c == '-' || c == '+')
			continue;
		if (c == '.')
			break;
		if (c >= '0' && c <= '9') {
			int nc = (int)(c - '0');
			a = nc + a * 10;
		}
		else {
			std::cout << num << " Not A Number!\n";
			return 0;
		}
	}
	if (exp)
		a = (int)(a * pow(10, exp));
	if (neg)
		return -a;
	return a;
}

float NumParse::Float(const std::string& num) {
	float a = 0;
	int c_z = 0;
	bool f = false;
	bool neg = false;
	int exp = 0;
	if (num[0] == '-')
		neg = true;
	for (unsigned int i = 0; i < num.size(); i++) {
		char c = num[i];
		if (i > 0 && (c == 'e' || c == 'E')) {
			std::string s = "";
			for (unsigned int j = i + 1; j < num.size(); j++) {
				s += num[j];
			}
			exp = NumParse::Integer(s);
			break;
		}
		if (c == '-' || c == '+')
			continue;
		if (c == '.') {
			c_z = 0;
			f = true;
			continue;
		}
		if (c >= '0' && c <= '9') {
			int nc = (int)(c - '0');
			a = nc + a * 10;
			if(f)
			c_z++;
		}
		else {
			std::cout << num << " Not A Number!\n";
			return 0.0f;
		}
	}
	if (exp)
		a = (float)(a * pow(10, exp));
	if(f)
	a = (float)(a / pow(10, c_z));
	if (neg)
		return -a;
	return a;
}

double NumParse::Double(const std::string& num) {
	double a = 0;
	int c_z = 0;
	bool f = false;
	bool neg = false;
	int exp = 0;
	if (num[0] == '-')
		neg = true;
	for (unsigned int i = 0; i < num.size(); i++) {
		char c = num[i];
		if (i > 0 && (c == 'e' || c == 'E')) {
			std::string s = "";
			for (unsigned int j = i + 1; j < num.size(); j++) {
				s += num[j];
			}
			exp = NumParse::Integer(s);
			break;
		}
		if (c == '-' || c == '+')
			continue;
		if (c == '.') {
			f = true;
			c_z = 0;
			continue;
		}
		if (c >= '0' && c <= '9') {
			int nc = (int)(c - '0');
			a = nc + a * 10;
			if (f)
			c_z++;
		}
		else {
			std::cout << num << " Not A Number!\n";
			return 0;
		}
	}
	if (exp)
		a = a * pow(10, exp);
	if(f)
	a /= pow(10, c_z);
	if (neg)
		return -a;
	return a;
}


#endif