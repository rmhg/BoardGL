class Shape{
private :
    unsigned int vc = 0;
    vec3f* arr;
    vec4f Color;
    vec2f* texArr;
    unsigned int gl_shape;
public :
    unsigned int index = 0;
    Shape(unsigned int, unsigned int, vec4f, std::vector<vec3f>);
    Shape(unsigned int, unsigned int, vec4f, std::vector<vec3f>, std::vector<vec2f>);

    void setGLFlag(unsigned int);
    void setColor(vec4f);
    void updVertices(std::vector<vec3f>);
    void updVertex(unsigned int , vec3f);

    void Scale(float);
    void Translate(vec3f);
    void Rotate(vec3f, float);

    vec3f* getPtr();
    vec4f getColor();
    vec2f* getTexCoords();

    unsigned int getGLFlag();
    unsigned int getVC();
};

Shape::Shape(unsigned int avc, unsigned int agl_shape, vec4f Col, std::vector<vec3f> data){
    vc = avc;
    gl_shape = agl_shape;
    Color = Col;
    arr = (vec3f*)malloc(vc*sizeof(vec3f));
    texArr = (vec2f*)malloc(vc*sizeof(vec2f));
    if(!arr)
    {
        std::cout << "Cant Initiate THe Shape \n";
        return;
    }
    for (unsigned int i = 0; i < vc;i++) {
        arr[i] = data[i];
        texArr[i] = vec2f();
    }
}

Shape::Shape(unsigned int avc, unsigned int agl_shape, vec4f Col, std::vector<vec3f> data, std::vector<vec2f> tex){
    vc = avc;
    gl_shape = agl_shape;
    Color = Col;
    arr = (vec3f*)malloc(vc*sizeof(vec3f));
    texArr = (vec2f*)malloc(vc*sizeof(vec2f));
    if(!arr)
    {
        std::cout << "Cant Initiate THe Shape \n";
        return;
    }
    for (unsigned int i = 0; i < vc;i++) {
        arr[i] = data[i];
        texArr[i] = tex[i];
    }
}

void Shape::setGLFlag(unsigned int glflag){
    gl_shape = glflag;
}

void Shape::setColor(vec4f Col){
    Color = Col;
}

void Shape::updVertices(std::vector<vec3f> data){
   for(unsigned int i = 0; i < vc;i++)
    arr[i] = data[i];
}

void Shape::updVertex(unsigned int index, vec3f vertex){
    if(index > vc - 1)
         std::cout << index <<  " OUT OF RANGLE\n";
    arr[index] = vertex;
}

void Shape::Scale(float sf){
   Matrix<float> Mat(4, 1, 1);
   Matrix<float> Trans = Transform::Scale(sf);
   for(unsigned int i = 0; i < vc;i++){
    Mat[0][0] = arr[i].x();
    Mat[1][0] = arr[i].y();
    Mat[2][0] = arr[i].z();
    Mat = Trans * Mat;

    arr[i].x() = Mat[0][0];
    arr[i].y() = Mat[1][0];
    arr[i].z() = Mat[2][0];

   }
}

void Shape::Translate(vec3f vt){
   Matrix<float> Mat(4, 1, 1);
   Matrix<float> Trans = Transform::Translate(vt);
   for(unsigned int i = 0; i < vc;i++){
    Mat[0][0] = arr[i].x();
    Mat[1][0] = arr[i].y();
    Mat[2][0] = arr[i].z();

    Mat = Trans * Mat;

    arr[i].x() = Mat[0][0];
    arr[i].y() = Mat[1][0];
    arr[i].z() = Mat[2][0];

   }
}

void Shape::Rotate(vec3f ax, float deg)
{
   Matrix<float> Mat(4, 1, 1);
   Matrix<float> Trans = Transform::Rotate(ax, deg);
   for(unsigned int i = 0; i < vc ;i++){
    Mat[0][0] = arr[i].x();
    Mat[1][0] = arr[i].y();
    Mat[2][0] = arr[i].z();

    Mat = Trans * Mat;

    arr[i].x() = Mat[0][0];
    arr[i].y() = Mat[1][0];
    arr[i].z() = Mat[2][0];

   }
}

vec3f* Shape::getPtr(){
        return arr;
}

vec4f Shape::getColor(){
   return Color;
}

vec2f* Shape::getTexCoords(){
   return texArr;
}

unsigned int Shape::getGLFlag(){
   return gl_shape;
}
unsigned int Shape::getVC(){
   return vc;
}
