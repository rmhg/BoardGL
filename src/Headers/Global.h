#define stringify(x) #x
#define STOP(msg) std::cout<<"STOPPED AT FILE : " <<__FILE__ << " | LINE : " <<  __LINE__ << "\nERROR : "  msg<<std::endl;exit(0);
#define cSTOP(msg) std::cout<<"STOPPED AT FILE : " <<__FILE__ << " | LINE : " <<  __LINE__ << "\nERROR : "  + msg<<std::endl;exit(0);
#define LF std::endl
#define sLF "\n"

#define RES "Res/"
#define UTILS "Headers/Utils/"
#define EXTERN "Headers/Extern/"
#define SHADERS "Headers/Shaders/"
#define DRAWING "Headers/Core/Drawing/"
#define PRIMITIVE "Headers/Core/Drawing/Primitive/"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <thread>
#include <vector>

#include "glad/glad.h"
#include "Utils/Utils.h"

#include "Utils/Matrix.h"
#include "Utils/Vecs.h"
#if 1
#include "Utils/vecVals.h"
#include "Utils/NumParser.h"
#include "Utils/File2String.h"
#include "Utils/OBJLoader.h"

#include "Utils/Transform.h"

#include "Console.h"
#include "Window/Window.h"

#include "Core/Buffers/VertexArray.h"
#include "Core/Buffers/VertexBuffer.h"
#include "Core/Shader/Shaders.h"
#include "Core/Drawing/Text/FontLoader.h"
#include "Core/Drawing/Texture/Texture.h"
#include "Core/Camera.h"
#include "Core/Drawing/Primitive/Drawable.h"
#include "Core/Buffers/DrawBuffer.h"


#include "Core/Drawing/Primitive/2D/Triangle.h"
#include "Core/Drawing/Primitive/2D/Rectangle.h"
#include "Core/Drawing/Primitive/2D/Line.h"
#include "Core/Drawing/Primitive/2D/Circle.h"
#include "Core/Drawing/Primitive/3D/Cube.h"

#include "Physics Engine/Params.h"
#include "Physics Engine/DynamicObject.h"
#include "Physics Engine/PhysicDrawable.h"
#include "Physics Engine/Collision.h"
#include "Physics Engine/PhysicsBuffer.h"

int Width = 1280;
int Height = 720;
unsigned int g_fps = 0;

void clearCharac(unsigned int n){
  std::string str = "";
  while(n--)
   str += "\b";
  std::cout << str;
}

bool isOpen = true;
unsigned int avg_FPS = 0;
unsigned int n_vfps = 0;
void showFPS(){
   while(isOpen){
       if (Show_FPS) {
           std::cout << "FPS : " << g_fps;clearCharac(16);
       }
       avg_FPS += g_fps;
       n_vfps++;
       g_fps = 0;
    std::this_thread::sleep_for(std::chrono::seconds(1));
   }
   std::cout << "Average FPS : " << (float)avg_FPS / n_vfps << LF;
}
void logGL() {
    std::cout << "OPEN GL VERSION : " << glGetString(GL_VERSION) << LF << "VENDOR : " <<  glGetString(GL_VENDOR) << LF;
}



#endif

