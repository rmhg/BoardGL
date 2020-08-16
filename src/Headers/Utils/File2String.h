#ifndef FILE2STRING_H
#define FILE2STRING_H

#include <iostream>
#include <fstream>
#include <sstream>


class File2String{
  std::string path = "";
  std::ifstream read;
  std::string content;
  public :
  File2String(std::string);
  std::string getString();
  void showFile();
};

File2String::File2String(std::string fpath):path(fpath){
  std::ifstream read(path.c_str());
  if(!read){
    std::cout << "File Not Found! At " + fpath + "\n";
    return;
  }
  content = "";
  try {
      std::stringstream ss;
	  ss << read.rdbuf();
	  content = ss.str();
  }
  catch (std::ifstream::failure e) {
	  std::cout << "FAILED IN FILE";
  }

  read.close();
}
std::string File2String::getString(){
     return content;
}
void File2String::showFile(){
  std::cout << content;
}

#endif