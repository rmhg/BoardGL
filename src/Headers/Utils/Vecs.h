
using namespace Basic;

template<typename type>
class Vector :public std::vector<type> {
public :
    unsigned int dims;
    Vector(unsigned int);
    Vector(std::initializer_list<type>);
    void operator*= (Matrix<type>);
    void operator*= (Vector<type>);
    void operator*= (type);
    void operator+= (Vector<type>);
    void operator-= (Vector<type>);
    void operator+= (type);
    void operator-= (type);
    void operator/= (type);
    
    Vector<type> operator* (Matrix<type>);
    Vector<type> operator* (Vector<type>);
    Vector<type> operator* (type);
    Vector<type> operator+ (Vector<type>);
    Vector<type> operator+ (type);
    Vector<type> operator- (Vector<type>);
    Vector<type> operator- (type);
    Vector<type> operator/ (type);

    float Mod();
    float Dot(Vector<type>);
    Vector<type> Cross(Vector<type>);
    Vector<type> Normalized();

    void Print();
};
template<typename type>
Vector<type>::Vector(unsigned int dimmensions) : dims(dimmensions) {
    this->resize(dimmensions);
}

template<typename type>
Vector<type>::Vector(std::initializer_list<type> arr) : std::vector<type>(arr), dims(arr.size()) {
}

template <typename type>
void Vector<type>::operator+= (Vector<type> av) {
    for (unsigned int i = 0; i < dims;i++)
        (*this)[i] += av[i];
}

template <typename type>
void Vector<type>::operator-= (Vector<type> av) {
    for (unsigned int i = 0; i < dims;i++)
        (*this)[i] -= av[i];
}

template <typename type>
Vector<type> Vector<type>::operator- (Vector<type> av) {
    Vector<type> tmp(dims);
    for (unsigned int i = 0; i < dims;i++)
        tmp[i] = (*this)[i] - av[i];
    return tmp;
}

template <typename type>
Vector<type> Vector<type>::operator+ (Vector<type> av) {
    Vector<type> tmp(dims);
    for (unsigned int i = 0; i < dims;i++)
        tmp[i] = (*this)[i] + av[i];
    return tmp;
}

template<typename type>
void Vector<type>::operator*= (Matrix<type> amat) {
    Vector<type> tmp(dims);
    for(unsigned int i = 0; i < dims;i++)
        for(unsigned int j = 0; j < dims;j++)
         tmp[i] += amat[i][j] * (*this)[j];
    (*this) = tmp;
}

template<typename type>
Vector<type> Vector<type>::operator* (Matrix<type> amat) {
    Vector<type> tmp(dims);
    for (unsigned int i = 0; i < dims;i++)
        for (unsigned int j = 0; j < dims;j++)
            tmp[i] += amat[i][j] * (*this)[j];
    return tmp;
}

template <typename type>
void Vector<type>::operator*= (Vector<type> av) {
    for (unsigned int i = 0; i < dims;i++)
        (*this)[i] *= av[i];
}


template <typename type>
Vector<type> Vector<type>::operator* (Vector<type> av) {
    Vector<type> tmp(dims);
    for (unsigned int i = 0; i < dims;i++)
        tmp[i] = (*this)[i] * av[i];
    return tmp;
}

template <typename type>
Vector<type> Vector<type>::operator* (type scalar) {
    Vector<type> tmp(dims);
    for (unsigned int i = 0; i < dims;i++)
        tmp[i] = (*this)[i] * scalar;
    return tmp;
}

template <typename type>
Vector<type> Vector<type>::operator+ (type scalar) {
    Vector<type> tmp(dims);
    for (unsigned int i = 0; i < dims;i++)
        tmp[i] = (*this)[i] + scalar;
    return tmp;
}

template <typename type>
Vector<type> Vector<type>::operator- (type scalar) {
    Vector<type> tmp(dims);
    for (unsigned int i = 0; i < dims;i++)
        tmp[i] = (*this)[i] - scalar;
    return tmp;
}

template <typename type>
Vector<type> Vector<type>::operator/ (type scalar) {
    if (scalar == 0) {
        STOP("CANT DIVIDE BY ZERO! VECTOR");
    }
    Vector<type> tmp(dims);
    for (unsigned int i = 0; i < dims;i++)
        tmp[i] = (*this)[i] / scalar;
    return tmp;
}

template <typename type>
void Vector<type>::operator/= (type scalar) {
    if (scalar == 0) {
        STOP("CANT DIVIDE BY ZERO! VECTOR");
    }
    for (unsigned int i = 0; i < dims;i++)
        (*this)[i] /= scalar;
}

template <typename type>
void Vector<type>::operator+= (type scalar) {
    for (unsigned int i = 0; i < dims;i++)
        (*this)[i] += scalar;
}

template <typename type>
void Vector<type>::operator-= (type scalar) {
    for (unsigned int i = 0; i < dims;i++)
        (*this)[i] -= scalar;
}

template <typename type>
void Vector<type>::operator*= (type scalar) {
    for (unsigned int i = 0; i < dims;i++)
        (*this)[i] *= scalar;
}



template <typename type>
float Vector<type>::Mod() {
    float s = 0.0f;
    for (unsigned int i = 0; i < 3; i++)
        s += (*this)[i] * (*this)[i];
    return sqrt(s);
}

template <typename type>
float Vector<type>::Dot(Vector<type> av) {
    float s = 0.0f;
    for (unsigned int i = 0; i < dims;i++)
        s += (*this)[i] * av[i];
    return s;
}

template<typename type>
Vector<type> Vector<type>::Cross(Vector<type> av) {
    Vector<type> tmp(dims);
    tmp[0] = (*this)[1] * av[2] - av[1] * (*this)[2];
    tmp[1] = -((*this)[0] * av[2] - av[0] * (*this)[2]);
    tmp[2] = (*this)[0] * av[1] - av[0] * (*this)[1];
    return tmp;
}

template<typename type>
Vector<type> Vector<type>::Normalized() {
    Vector<type> tmp(dims);
    float mod = Mod();
    for (unsigned int i = 0; i < dims;i++)
        tmp[i] = (*this)[i] / mod;
    return tmp;
}


template<typename type>
void Vector<type>::Print() {
    for (unsigned int i = 0; i < dims;i++)
        std::cout << (*this)[i] << std::endl;
}





class vec2f : public Vector<float> {

public:
    float& x = (*this)[0];
    float& y = (*this)[1];
    vec2f();
    vec2f(Vector<float> a) : Vector<float>(2) {
        for (unsigned int i = 0; i < dims && i < a.dims;i++) 
            (*this)[i] = a[i];
    }
    vec2f(const vec2f&);
    vec2f& operator= (const vec2f&);
    vec2f(float, float);
};

vec2f::vec2f() : Vector<float>(2){}
vec2f::vec2f(float x, float y) : Vector<float>(2){
    (*this)[0] = x;(*this)[1] = y;
}
vec2f& vec2f::operator= (const vec2f& a) {
    loop(dims, (*this)[i] = a[i]);
    return (*this);
}
vec2f::vec2f(const vec2f& v) : Vector<float>(2) {
    loop(dims, (*this)[i] = v[i]);
}

class vec3f : public Vector<float> {
public:
    float& x = (*this)[0];
    float& y = (*this)[1];
    float& z = (*this)[2];
    vec3f();
    vec3f(Vector<float> a) : Vector<float>(3) {
        for (unsigned int i = 0; i < dims && i < a.dims;i++)
            (*this)[i] = a[i];
    }
    vec3f(const vec3f&);
    vec3f(vec2f, float z = 0.0f);
    vec3f(float, float, float);
    vec3f& operator= (const vec3f&);
};

vec3f::vec3f() : Vector<float>(3){
    x = (*this)[0];
    y = (*this)[1];
    z = (*this)[2];

}
vec3f::vec3f(vec2f vec, float z) : Vector<float>(3){
    (*this)[0] = vec[0];
    (*this)[1] = vec[1];
    (*this)[2] = z;
    x = (*this)[0];
    y = (*this)[1];
    z = (*this)[2];
}
vec3f::vec3f(float x, float y, float z) : Vector<float>(3){
    (*this)[0] = x;(*this)[1] = y;(*this)[2] = z;
}
vec3f& vec3f::operator= (const vec3f& a) {
    loop(dims, (*this)[i] = a[i]);
    return (*this);
}
vec3f::vec3f(const vec3f& v) : Vector<float>(3) {
    loop(dims, (*this)[i] = v[i]);
}

class vec4f : public Vector<float> {
public:
    float& x = (*this)[0];
    float& y = (*this)[1];
    float& z = (*this)[2];
    float& a = (*this)[3];
    vec4f();
    vec4f(Vector<float> a) : Vector<float>(4) {
        for (unsigned int i = 0; i < dims && i < a.dims;i++)
            (*this)[i] = a[i];
    }
    vec4f(const vec4f&);
    vec4f& operator= (const vec4f&);
    vec4f(vec3f, float a = 0.0f);
    vec4f(float, float, float, float);

    
};

vec4f::vec4f() : Vector<float>(4){}
vec4f::vec4f(vec3f vec, float a) : Vector<float>(4){
    (*this)[0] = vec[0];
    (*this)[1] = vec[1];
    (*this)[2] = vec[2];
    (*this)[3] = a;
}
vec4f::vec4f(const vec4f& v) : Vector<float>(4){
    loop(dims, (*this)[i] = v[i]);
}
vec4f::vec4f(float x, float y, float z, float a) : Vector<float>(4){

    (*this)[0] = x;(*this)[1] = y;(*this)[2] = z;(*this)[3] = a;
}
vec4f& vec4f::operator= (const vec4f& a) {
    loop(dims, (*this)[i] = a[i]);
    return (*this);
}



class vec2d : public Vector<double> {
public:
    double& x = (*this)[0];
    double& y = (*this)[1];
    vec2d();
    vec2d(const vec2d&);
    vec2d(Vector<double> a) : Vector<double>(2) {
        for (unsigned int i = 0; i < dims && i < a.dims;i++)
            (*this)[i] = a[i];
    }
    vec2d& operator= (const vec2d&);

    vec2d(double, double);
};

vec2d::vec2d() : Vector<double>(2){}
vec2d::vec2d(double x, double y) : Vector<double>(2){
    (*this)[0] = x;(*this)[1] = y;
}
vec2d& vec2d::operator= (const vec2d& a) {
    loop(dims, (*this)[i] = a[i]);
    return (*this);
}
vec2d::vec2d(const vec2d& v) : Vector<double>(2) {
    loop(dims, (*this)[i] = v[i]);
}

class vec3d : public Vector<double> {
public:
    double& x = (*this)[0];
    double& y = (*this)[1];
    double& z = (*this)[2];
    vec3d();
    vec3d(const vec3d&);
    vec3d(Vector<double> a) : Vector<double>(3) {
        for (unsigned int i = 0; i < dims && i < a.dims;i++)
            (*this)[i] = a[i];
    }
    vec3d& operator= (const vec3d&);
    vec3d(double, double, double);
};

vec3d::vec3d() : Vector<double>(3){}
vec3d::vec3d(double x, double y, double z) : Vector<double>(3){
    (*this)[0] = x;(*this)[1] = y;(*this)[2] = z;
}
vec3d::vec3d(const vec3d& v) : Vector<double>(3) {
    loop(dims, (*this)[i] = v[i]);
}
vec3d& vec3d::operator= (const vec3d& a) {
    loop(dims, (*this)[i] = a[i]);
    return (*this);
}
class vec4d : public Vector<double> {
public:
    double& x = (*this)[0];
    double& y = (*this)[1];
    double& z = (*this)[2];
    double& a = (*this)[3];
    vec4d();
    vec4d(Vector<double> a) : Vector<double>(4) {
        for (unsigned int i = 0; i < dims && i < a.dims;i++)
            (*this)[i] = a[i];
    }
    vec4d(const vec4d&);
    vec4d& operator= (const vec4d&);
    vec4d(double, double, double, double);
};

vec4d::vec4d() : Vector<double>(4){}
vec4d::vec4d(double x, double y, double z, double a) : Vector<double>(4){
    (*this)[0] = x;(*this)[1] = y;(*this)[2] = z;(*this)[3] = a;
}
vec4d& vec4d::operator= (const vec4d& a) {
    loop(dims, (*this)[i] = a[i]);
    return (*this);
}
vec4d::vec4d(const vec4d& v) : Vector<double>(4) {
    loop(dims, (*this)[i] = v[i]);
}
class vec2i : public Vector<int> {
public:
    int& x = (*this)[0];
    int& y = (*this)[1];
    vec2i();
    vec2i(Vector<int> a) : Vector<int>(2) {
        for (unsigned int i = 0; i < dims && i < a.dims;i++)
            (*this)[i] = a[i];
    }
    vec2i(const vec2i&);
    vec2i& operator= (const vec2i&);
    vec2i(int, int);
};

vec2i::vec2i() : Vector<int>(2){}
vec2i::vec2i(int x, int y) : Vector<int>(2){
    (*this)[0] = x;(*this)[1] = y;
}
vec2i& vec2i::operator= (const vec2i& a) {
    loop(dims, (*this)[i] = a[i]);
    return (*this);
}
vec2i::vec2i(const vec2i& v) : Vector<int>(2) {
    loop(dims, (*this)[i] = v[i]);
}
class vec3i : public Vector<int> {
public:
    int& x = (*this)[0];
    int& y = (*this)[1];
    int& z = (*this)[2];
    vec3i();
    vec3i(Vector<int> a) : Vector<int>(3) {
        for (unsigned int i = 0; i < dims && i < a.dims;i++)
            (*this)[i] = a[i];
    }
    vec3i(const vec3i&);
    vec3i& operator= (const vec3i&);
    vec3i(int, int, int);
};

vec3i::vec3i() : Vector<int>(3){}
vec3i::vec3i(int x, int y, int z) : Vector<int>(3){
    (*this)[0] = x;(*this)[1] = y;(*this)[2] = z;
}
vec3i& vec3i::operator= (const vec3i& a) {
    loop(dims, (*this)[i] = a[i]);
    return (*this);
}
vec3i::vec3i(const vec3i& v) : Vector<int>(3) {
    loop(dims, (*this)[i] = v[i]);
}
class vec4i : public Vector<int> {
public:
    int& x = (*this)[0];
    int& y = (*this)[1];
    int& z = (*this)[2];
    int& a = (*this)[3];
    vec4i();
    vec4i(Vector<int> a) : Vector<int>(4) {
        for (unsigned int i = 0; i < dims && i < a.dims;i++)
            (*this)[i] = a[i];
    }
    vec4i(const vec4i&);
    vec4i& operator= (const vec4i&);
    vec4i(int, int, int, int);
};

vec4i::vec4i() : Vector<int>(4){}
vec4i::vec4i(int x, int y, int z, int a) : Vector<int>(4){
    (*this)[0] = x;(*this)[1] = y;(*this)[2] = z;(*this)[3] = a;
}
vec4i::vec4i(const vec4i& v) : Vector<int>(4) {
    loop(dims, (*this)[i] = v[i]);
}
vec4i& vec4i::operator= (const vec4i& a) {
    loop(dims, (*this)[i] = a[i]);
    return (*this);
}

