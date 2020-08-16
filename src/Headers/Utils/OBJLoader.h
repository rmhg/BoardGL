#pragma once
#ifndef OBJLOADER_H
#define OBJLOADER_H
#include "FileParser.h"

class OBJLoader :public FileParser {
public:
    OBJLoader(const std::string&);
    std::vector<float> vert;
    std::vector<float> normal;
    std::vector<float> tex;
    std::vector<unsigned int> indices;
    void nextLine(std::string line) override;
};
OBJLoader::OBJLoader(const std::string& file) : FileParser(file) {
    Load();
}
void OBJLoader::nextLine(std::string line) {
    std::string str = "";
    switch (line[0]) {
    case 'v': {
        switch (line[1]) {
        case 't': {str = "";
            for (unsigned int i = 2; i < line.size(); i++) {
                if (line[i] == ' ') {
                    if (str.length()) {
                        tex.push_back(NumParse::Float(str));
                    }

                    str = "";
                    continue;
                }
                str += line[i];
            }
            tex.push_back(NumParse::Float(str));
        }
                break;
        case 'n': {
            str = "";
            for (unsigned int i = 2; i < line.size(); i++) {
                if (line[i] == ' ') {
                    if (str.length()) {
                        normal.push_back(NumParse::Float(str));
                    }

                    str = "";
                    continue;
                }
                str += line[i];
            }
            normal.push_back(NumParse::Float(str));
        }
                break;
        case ' ': {
            str = "";
            for (unsigned int i = 2; i < line.size(); i++) {
                if (line[i] == ' ') {
                    if (str.length()) {
                        vert.push_back(NumParse::Float(str));
                    }

                    str = "";
                    continue;
                }
                str += line[i];
            }
            vert.push_back(NumParse::Float(str));
        }
                break;
        default: {}
        }
    }
            break;
    case 'f': {
        str = "";
        for (unsigned int i = 2; i < line.size(); i++) {
            if (line[i] == ' ' || line[i] == '/') {

                if (str.length()) {
                    indices.push_back(NumParse::Integer(str));

                }

                str = "";
                continue;
            }
            str += line[i];
        }
        indices.push_back(NumParse::Integer(str));

    }
            break;
    }
}


#endif