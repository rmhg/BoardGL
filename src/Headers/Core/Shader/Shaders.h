#ifndef SHADERS_H
#define SHADERS_H

#include <map>
#include "Utils/File2String.h"
#include "RawShader.h"
#include <cstdarg>

class Shader{
private :
     std::map<std::string , unsigned int> cache;
     unsigned int id;
     char log[512];
     static std::string LoadShader(std::string path);
     std::vector<unsigned int> sids;
     unsigned int types[3] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER};
public :
    Shader(std::vector<std::string>);
    Shader(int ,std::vector<RawShader>);
    ~Shader();

    void Bind();
    void unBind();

    unsigned int getID();
    void CombineShaders();

    void Init();
    unsigned int getUniform(const std::string&);

    void setUniform(std::string, int);

    void setUniform(std::string , vec3f);
    void setUniform(std::string , vec4f);

    void setUniform(std::string, unsigned int, int*);

    void setUniform(std::string , Matrix<float>);

};

Shader::Shader(std::vector<std::string> data){
    std::string ssrc = "";
   for(unsigned int i = 0; i < data.size(); i++){
     int sc = 1;
     unsigned int id;
     id = glCreateShader(types[i]);
     ssrc = LoadShader(data[i]);
     const char* src = ssrc.c_str();
     glShaderSource(id,1, &src,NULL);
     glCompileShader(id);
     glGetShaderiv(id,GL_COMPILE_STATUS,&sc);
     if(!sc){
         glGetShaderInfoLog(id,512,NULL,log);
         std::cout << "ERROR IN SHADER : \n" << log << std::endl;
     }
     sids.push_back(id);
   }
   CombineShaders();
}
Shader::Shader(int k,std::vector<RawShader> data){
    std::string ssrc = "";
   for(unsigned int i = 0; i < data.size(); i++){
     int sc = 1;
     unsigned int id;
     id = glCreateShader(types[i]);
     ssrc = data[i].getUpdatedSource();
     const char* src = ssrc.c_str();
     glShaderSource(id,1, &src,NULL);
     glCompileShader(id);
     glGetShaderiv(id,GL_COMPILE_STATUS,&sc);
     if(!sc){
         glGetShaderInfoLog(id,512,NULL,log);
         std::cout << "ERROR IN SHADER : \n" << log << std::endl;
     }
     sids.push_back(id);
   }
   CombineShaders();
}



std::string Shader::LoadShader(std::string path){
    return File2String(path).getString();
}

unsigned int Shader::getID(){
   return id;
}

void Shader::CombineShaders(){
   unsigned int prg = glCreateProgram();

   for(unsigned int i = 0;i < sids.size();i++){
       glAttachShader(prg,sids[i]);
   }
   glLinkProgram(prg);
   glUseProgram(prg);

   for(unsigned int i = 0; i < sids.size();i++){
     glDeleteShader(sids[i]);
   }
   id = prg;
}

unsigned int Shader::getUniform(const std::string& name){
  unsigned int loc = 0;
  auto i = cache.find(name);
  if(i != cache.end())
    return i->second;
  loc = glGetUniformLocation(id, name.c_str());
  cache.insert(std::pair<std::string, unsigned int>(name, loc));
  return loc;
}

void Shader::Bind() {
    glUseProgram(id);
}
void Shader::unBind() {
    glUseProgram(0);
}

void Shader::setUniform(std::string name, int val) {
    glUniform1i(getUniform(name), val);
}

void Shader::setUniform(std::string name, unsigned int count, int* arr) {
    glUniform1iv(getUniform(name), count, arr);
}

void Shader::setUniform(std::string name, vec3f vec){
  float arr[3] = {vec.x , vec.y , vec.z};
  glUniform3fv(getUniform(name), 1, arr);
}
void Shader::setUniform(std::string name, vec4f vec){
  float arr[4] = {vec.x , vec.y , vec.z, vec.a};
  glUniform4fv(getUniform(name), 1, arr);
}



void Shader::setUniform(std::string name, Matrix<float> mat){
   glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, mat.getLinearPtr(true));
}

Shader::~Shader(){

}


#endif