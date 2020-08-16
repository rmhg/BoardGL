#pragma once
#ifndef FILE_PARSER_H
#define FILE_PARSER_H

class FileParser {

private:
	std::string file_path;
	std::string src;
public:
	FileParser(const std::string&);
	void Load();
	inline virtual void nextLine(std::string) = 0;
};

FileParser::FileParser(const std::string& file_path){
	src = File2String(file_path).getString();
	
}
void FileParser::Load() {
	std::string line = "";
	char ch;
	int i = 0;
	while (true) {
		if (i == src.size())
			break;
		ch = src[i];
		if (ch == '\n') {
			if(line.length())
			nextLine(line);
		line = "";
		}
		else
		 line += ch;
		i++;
	}
}


#endif