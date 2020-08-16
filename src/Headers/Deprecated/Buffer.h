
#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H
#include <cstdarg>
#include <vector>

struct VertexData {
    float pos[3];
    float Color[4];
    float TexCoords[2];
};

struct MetaVertex{
   unsigned int id_s = 0;
   unsigned int c_s = 0;
   unsigned int e_s = 4;
};

template <typename type>
class VertexBuffer{

private :
    unsigned int id;
    unsigned int target;
    unsigned int meth;
    unsigned int type_c;
    unsigned int size;
    unsigned int e_size;
    unsigned int mv_w = 0;

    std::vector<type> hold;
    std::vector<MetaVertex> mv;
    void init();
public :
    VertexBuffer();
    VertexBuffer(unsigned int , unsigned int ameth = GL_DYNAMIC_DRAW);
    ~VertexBuffer();

    void VertexAttrib(int,...);
    void VertexData(std::vector<type>);
    void updData(unsigned int,unsigned int, Vector<float>*);
    void delBuffer();
    void updBuffer(std::vector<type>);
    void updVertexData(unsigned int ,std::vector<type>);
    type* show();

    inline void WireFrameMode(bool);
    inline void DrawBuffer();

    unsigned int getID();
    unsigned int getLen();
};

template<typename type>
VertexBuffer<type>::VertexBuffer(){
    size = 0;
   target = GL_ARRAY_BUFFER;
   meth = GL_DYNAMIC_DRAW;
   type_c = 0;
   e_size = sizeof(type);
   glGenBuffers(1, &id);
   glBindBuffer(target, id);
}

template <typename type>
VertexBuffer<type>::VertexBuffer(unsigned int atar, unsigned int ameth) : target(atar), meth(ameth){
   type_c = 0;
   e_size = sizeof(type);
   glGenBuffers(1, &id);
   glBindBuffer(target, id);
}

template <typename type>
void VertexBuffer<type>::init(){
    glBufferData(target, hold.size() * e_size, &hold[0], meth);
}

template <typename type>
void VertexBuffer<type>::VertexAttrib(int n,...){
    va_list vl;
    va_start(vl, n);
    int s = 0;
    int w = 0;
    for(int i = 0; i < n; i++){
        MetaVertex tmp;
        tmp.id_s = i;
        int vc = va_arg(vl, int);
        tmp.c_s = vc;
        tmp.e_s = 4;
        w += tmp.c_s;
        mv.push_back(tmp);
    }
    mv_w = w;
    for(int i = 0; i < n; i++){
        s += mv[i].c_s;
        glVertexAttribPointer(i , mv[i].c_s , GL_FLOAT, GL_FALSE, w * e_size , (void*)((s - mv[i].c_s)*e_size));
        glEnableVertexAttribArray(i);
    }
}


template <typename type>
void VertexBuffer<type>::VertexData(std::vector<type> data){
   for(unsigned int i = 0; i < data.size(); i++)
      hold.push_back(data[i]);
   init();
}

template <typename type>
void VertexBuffer<type>::updData(unsigned int id, unsigned int index, Vector<float>* vec){

   if(id > mv.size() - 1){
    std::cout << "OUT OF RANGE";
    return;
   }
   int s = 0;
   for(int i = 0;i < id;s += mv[i++].c_s);
   int curr = index * mv_w + s;
   if((curr + mv[id].c_s) > getLen()){
    std::cout << "OUT OF RANGE";
    return;
   }
   switch(vec->dims){
case 2:  glBufferSubData(target, curr * e_size, sizeof(float), &((vec2f*)vec)->x());
         glBufferSubData(target, (curr + 1) * e_size, sizeof(float), &((vec2f*)vec)->y());
    break;
case 3:  glBufferSubData(target, curr * e_size, sizeof(float), &((vec3f*)vec)->x());
         glBufferSubData(target, (curr + 1) * e_size, sizeof(float), &((vec3f*)vec)->y());
         glBufferSubData(target, (curr + 2) * e_size, sizeof(float), &((vec3f*)vec)->z());
    break;
case 4:  glBufferSubData(target, curr * e_size, sizeof(float), &((vec4f*)vec)->x());
         glBufferSubData(target, (curr + 1) * e_size, sizeof(float), &((vec4f*)vec)->y());
         glBufferSubData(target, (curr + 2) * e_size, sizeof(float), &((vec4f*)vec)->z());
         glBufferSubData(target, (curr + 3) * e_size, sizeof(float), &((vec4f*)vec)->a());

   }

}

template <typename type>
void VertexBuffer<type>::updBuffer(std::vector<type> data){
   glBufferSubData(target, 0, data.size() * e_size, &data[0]);
}

template <typename type>
void VertexBuffer<type>::updVertexData(unsigned int index, std::vector<type> VertexData){
   glBufferSubData(target, index * (mv_w * e_size), VertexData.size() * e_size, &VertexData[0]);
}


template <typename type>
type* VertexBuffer<type>::show(){
 for(int i = 0 ; i < hold.size(); i++){
    std::cout << hold[i] << ", ";
 }
 return &hold[0];
}

template <typename type>
unsigned int VertexBuffer<type>::getID(){
   return id;
}

template <typename type>
unsigned int VertexBuffer<type>::getLen(){
  return hold.size();
}

template <typename type>
void VertexBuffer<type>::delBuffer(){
  glDeleteBuffers(1, &id);
}

template <typename type>
void VertexBuffer<type>::DrawBuffer(){
   switch(target){
case GL_ARRAY_BUFFER:glDrawArrays(GL_TRIANGLES, 0, hold.size());
    break;
case GL_ELEMENT_ARRAY_BUFFER: glDrawElements(GL_TRIANGLES, hold.size(), GL_UNSIGNED_INT, nullptr);
    break;
   }
}

template <typename type>
void VertexBuffer<type>::WireFrameMode(bool on){
   if(on)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

template <typename type>
VertexBuffer<type>::~VertexBuffer(){
   delBuffer();
}


#endif

