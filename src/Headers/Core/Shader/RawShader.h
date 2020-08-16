#pragma once
#ifndef RAWSHADER_H
#define RAWSHADER_H


class RawShader {
private:
	std::string rawsrc;
	std::string updsrc;
public :
	RawShader(const std::string&);

	void addDefine(std::string, std::string);
	void addLine(unsigned int , std::string);
	std::string getUpdatedSource();
	std::string getRawSource();
};

RawShader::RawShader(const std::string& file) {
	rawsrc = File2String(file).getString();
	updsrc = rawsrc;
}

void RawShader::addDefine(std::string name, std::string val) {
	std::string def = "\n#define " + name + " " + val + "\n";
	for (unsigned int i = 0; i < updsrc.size();i++) {
		if (updsrc[i] == '\n') {
		   
		}
	}
}

void RawShader::addLine(unsigned int line_no, std::string line) {
	
}

std::string RawShader::getUpdatedSource() { return updsrc; }
std::string RawShader::getRawSource() { return rawsrc; }

#endif