#ifndef Window_H
#define Window_H
#include "GLFW/glfw3.h"
#include <functional>

struct Mouse {
    vec2d pos;
    vec2d sc;
    int button;
    int action;
    int mod;
    vec2d posg(int Width, int Height) {
        vec2d tmp;
        tmp.x = (pos.x - Width / 2.0f) / (Width / 2.0f);
        tmp.y = (Height / 2.0f - pos.y) / (Height / 2.0f);
        return tmp;
    }
};


struct Key {
    int key;
    int action;
    int scancode;
    int mod;
};

struct Screen {
    vec2i size, pos;
};

class Event {
public :
    Mouse mouse;
    Screen screen;
    Key key;
    enum ACTION {
     PRESS = GLFW_PRESS, 
     RELEASED = GLFW_RELEASE, 
     REPEAT = GLFW_REPEAT,
    };
    enum MOUSE {
     RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
     MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
     LEFT = GLFW_MOUSE_BUTTON_LEFT,
    };

    std::function<void(Event*)> onClick;
    std::function<void(Event*)> onMouseMove;
    std::function<void(Event*)> onResize;
    std::function<void(Event*)> onKeyPress;
    std::function<void(Event*)> onScroll;
    std::function<void(Event*)> onWindowDrag;
};

class InterWindowObject {


};

class Window
{
private :
    GLFWwindow* Win;
    int width, height;
    std::string title;
public :
    static bool iGlad;
    Event event;
    static void InitWindow();

    void InitEvents();
    Window(int,int,std::string);
    void InitGL();
    inline static void InitGlad();

    vec2d getMousePos();
    GLFWwindow* getWinPointer();

    inline void ClearColor(vec4f);
    
    inline void setObj(void*);
    void* getObj();
    std::string getTitle();
    void VSync(unsigned int = 1);

    bool isOpen();
    void Update();
	void Close();
    static void CloseAll();

    ~Window();
};

bool Window::iGlad = false;

void Window::InitWindow() {
   glfwInit();
}

Window::Window(int w,int h,std::string t):width(w),height(h),title(t){
  
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   Win = glfwCreateWindow(width,height,title.c_str(),NULL,NULL);
   if(Win == NULL){
      throw "Failed To Create The Window!";
   }
   glfwSetWindowUserPointer(Win, (void*)&event);
}

void Window::InitEvents() {
   
   if(event.onClick)
   glfwSetMouseButtonCallback(Win,[](GLFWwindow* win, int but, int ac, int mods)-> void{
       Event* e = (Event*)glfwGetWindowUserPointer(win);
       glfwGetCursorPos(win, &e->mouse.pos.x, &e->mouse.pos.y);
       e->mouse.button = but;e->mouse.action = ac;e->mouse.mod = mods;
       e->onClick(e);
    });
   if (event.onResize)
   glfwSetFramebufferSizeCallback(Win, [](GLFWwindow* win, int, int)->void{
       Event* e = (Event*)glfwGetWindowUserPointer(win);
       glfwGetWindowSize(win, &e->screen.size.x, &e->screen.size.y);
       e->onResize(e);
   });

   if(event.onKeyPress)
   glfwSetKeyCallback(Win, [](GLFWwindow* win, int key, int sc,int ac, int mod)->void {
       Event* e = (Event*)glfwGetWindowUserPointer(win);
       e->key.key = key;e->key.action = ac;e->key.scancode = sc;e->key.mod = mod;
       e->onKeyPress(e);
    });

   if (event.onMouseMove)
   glfwSetCursorPosCallback(Win, [](GLFWwindow* win, double x, double y)-> void{
       Event* e = (Event*)glfwGetWindowUserPointer(win);
       e->mouse.pos.x = x;e->mouse.pos.y = y;
       e->onMouseMove(e);
   });

   if (event.onScroll)
   glfwSetScrollCallback(Win, [](GLFWwindow * win, double xoff, double yoff)-> void{
       Event* e = (Event*)glfwGetWindowUserPointer(win);
       e->mouse.sc.x = xoff;
       e->mouse.sc.y = yoff;
       e->onScroll(e);
   });

}

void Window::VSync(unsigned int v) {
    glfwSwapInterval(v);
}

vec2d Window::getMousePos(){
     vec2d coords;
     glfwGetCursorPos(Win,&coords.x,&coords.y);
     return coords;
}


inline void Window::InitGL(){
   glfwMakeContextCurrent(Win);
   
}

void Window::InitGlad() {
    if(!iGlad)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        STOP("Cant Initialized The Glad!");
    }
    Window::iGlad = true;
}

GLFWwindow* Window::getWinPointer(){
  return Win;
}


bool Window::isOpen(){
 int of = glfwWindowShouldClose(Win);
 return !of;
}

void Window::Update(){
  glfwSwapBuffers(Win);
  glfwPollEvents();
}

void Window::Close() {
    glfwDestroyWindow(Win);
}
void Window::CloseAll() {
	glfwTerminate();
}


void Window::ClearColor(vec4f Color){
    glClearColor(Color.x, Color.y, Color.z, Color.a);
   glClear(GL_COLOR_BUFFER_BIT);
}

void Window::setObj(void* Object) {
    glfwSetWindowUserPointer(Win,Object);
}

void* Window::getObj() {
    return glfwGetWindowUserPointer(Win);
}

std::string Window::getTitle() {
    return title;
}

Window::~Window(){
}
#endif
