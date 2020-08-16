#ifndef FILEINTERFACE_H
#define FILEINTERFACE_H

#include <fstream>

class FileInterface {
private :
	std::string filePath;
	std::fstream ffile;
	bool closed = false;
public :
	FileInterface(const std::string&);
	~FileInterface();
	void addLine(std::string);
	void addStr(std::string);
	void Close();
};
FileInterface::FileInterface(const std::string& file) : filePath(file) {
	ffile = std::fstream(filePath, std::ios::app);
	if (!ffile) {
		std::cout << file << " File Is NOt Open | FSTREAM\n";
		return;
	}
}
void FileInterface::addLine(std::string line) {
	ffile << line << "\n";
}
void FileInterface::addStr(std::string str) {
	ffile << str ;
}
void FileInterface::Close() {
	closed = true;
	ffile.close();
}
FileInterface::~FileInterface() {
	if (!closed)
		Close();
}


#endif