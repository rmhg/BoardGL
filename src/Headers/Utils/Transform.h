
#define PI 3.14159265359
#define toRad(deg)  (float)((PI / 180) * deg);

class Transform {

public :
	static Matrix<float> Rotate(vec3f,float);
	static Matrix<float> Translate(vec3f);
	static Matrix<float> Scale(float);
	static Matrix<float> TranslateAndScale(vec3f, float );
	static Matrix<float> Prospective(float, float, float, float);
	static Matrix<float> Ortho();
    static void vRot2D(vec2f&, vec2f, float);
};

Matrix<float> Transform::Rotate(vec3f rv, float fr){
   Matrix<float> id = Matrix<float>::getIdentity(4);
   float rad = (float)(PI / 180) * fr;
   float dc =  cos(rad);
   float ds =  sin(rad);
   id[0][0] = dc + rv.x * rv.x * (1 - dc);
   id[1][1] = dc + rv.y * rv.y * (1 - dc);
   id[2][2] = dc + rv.z * rv.z * (1 - dc);

   id[0][1] = rv.x * rv.y * (1 - dc) - rv.z * ds;
   id[0][2] = rv.x * rv.z * (1 - dc) + rv.y * ds;

   id[1][0] = rv.y * rv.x * (1 - dc) + rv.z * ds;
   id[1][2] = rv.y * rv.z * (1 - dc) - rv.x * ds;

   id[2][0] = rv.z * rv.x * (1 - dc) - rv.y * ds;
   id[2][1] = rv.z * rv.y * (1 - dc) + rv.x * ds;

   return id;
}

Matrix<float> Transform::Translate(vec3f vt){
    Matrix<float> id = Matrix<float>::getIdentity(4);
    id[0][3] = vt.x;
    id[1][3] = vt.y;
    id[2][3] = vt.z;
    return id;
}

Matrix<float> Transform::TranslateAndScale(vec3f vt, float sf){
    Matrix<float> id = Matrix<float>::getIdentity(4);
    id[0][3] = vt.x;
    id[1][3] = vt.y;
    id[2][3] = vt.z;

    id[0][0] = sf;
    id[1][1] = sf;
    id[2][2] = sf;

    return id;
}

Matrix<float> Transform::Scale(float sf){
    Matrix<float> id = Matrix<float>::getIdentity(4);
    id[0][0] = sf;
    id[1][1] = sf;
    id[2][2] = sf;
    return id;
}

Matrix<float> Transform::Prospective(float fov, float asp, float near, float far){
    Matrix<float> proj = Matrix<float>::getIdentity(4);
    fov = (float)(PI / 180) * fov;
    float tfov = tan(fov / 2.0f);
    float zm = far - near;
    float zp = far + near;
    proj[0][0] = (1/tfov)/asp;
    proj[1][1] = (1/tfov);
    proj[2][2] = -zp/zm;
    proj[2][3] = -(2*far*near)/zm;
    proj[3][3] = 0.0f;
    proj[3][2] = -1;
    return proj;
}


void Transform::vRot2D(vec2f& sub, vec2f const_v, float deg) {
    float rad = toRad(deg);
    float mod = (sub - const_v).Mod();
    sub.x = const_v.x + mod * cos(rad);
    sub.y = const_v.y + mod * sin(rad);
}


Matrix<float> Transform::Ortho(){
     return Matrix<float>::getIdentity(4);
}
