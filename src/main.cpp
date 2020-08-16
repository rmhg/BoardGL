bool Show_FPS = false;
#include "Global.h"

 void LevelCreate(const std::string& level,std::vector<PhysicsDrawable>& blocks, int r, int c) {
 
 
     for (int i = 0; i < r; i++) {
         for (int j = 0; j < c;j++) {
            char ch = level[i * c + j];
            switch (ch) {
            case '#': {
                PhysicsDrawable StaticObj(vec3f(-1.0f + 0.2f * j, 1.0f - 0.2f * i, -1.0f), vec2f(0.2f, 0.2f), BGL::Color::NOCOLOR, 100.0f, 1);
                StaticObj.isDynamic = false;
                blocks.push_back(StaticObj);
            }
                break;
            case 'P': {
                PhysicsDrawable phy(vec3f(-1.0f + 0.2f * j, 1.0f - 0.2f * i, -1.0f), vec2f(0.2f, 0.2f), BGL::Color::BLUE, 100.0f, 0);
                phy.setColor(BGL::Color::BLUE);
                phy.isDynamic = true;
                blocks.push_back(phy);
            }
                    break;
            case 'W': {
                PhysicsDrawable phy(vec3f(-1.0f + 0.2f * j, 1.0f - 0.2f * i, -1.0f), vec2f(0.2f, 0.2f), BGL::Color::NOCOLOR, 100.0f, 2);
                phy.isDynamic = false;
                blocks.push_back(phy);
            }
                    break;
            }
         }
     }

 }


#ifndef Test
float i = 0;
int main() {
    int c = 20;
    std::string level = "# # # # # # # # # # "
                        "  P                 "
                        "                    " 
                        "                    " 
                        " WWW                "
                        "                    "
                        "       WWW          "
                        "                    "
                        "                    "
                        "## #### ### # # # # ";

    std::vector<PhysicsDrawable> dl;
    std::vector<unsigned int> did; 
    
    {
    LevelCreate(level, dl, level.size() / c, c);
    for (unsigned int i = 0; i < dl.size(); i++)
        if (dl[i].isDynamic)
            did.push_back(i);
    }

#if 1
    TimeObject a;
    Window::InitWindow();
    initRandom();
    std::thread fp(showFPS);
    Window* win = new Window(1280, 720, "BoardGL");
    win->InitGL();
    Window::InitGlad();
    logGL();
    win->event.onResize = [](Event* e) {
        glViewport(0, 0, e->screen.size.x, e->screen.size.y);
    };
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Texture::GET_MAX_SLOT();
    Shader shader({SHADERS"vert.vshd", SHADERS"frag.fshd"});
    Texture Ground(RES"GroundTexture.jpg");
    Texture (RES"WoodTexture.jpg").BindTextureSlot(1);
    Ground.BindTextureSlot(0);
    int* texture = new int[Texture::MAX_SLOT];
    for (int i = 0; i < Texture::MAX_SLOT;i++)
        texture[i] = i;
    shader.setUniform("texturer", Texture::MAX_SLOT, texture);
    delete[] texture;
    bool space = false;
#endif
    DrawBuffer dbuf;
    PhysicsBuffer pbuf;

    for (PhysicsDrawable& obj : dl) {
        dbuf.addDrawable(&obj);
        pbuf.addObject(&obj);
    }

    win->event.onClick = [&](Event* e)->void {
        if (e->mouse.action == Event::ACTION::PRESS) {
            vec2d mpos = e->mouse.pos;
        }
    };

    Camera camera;

    win->event.onKeyPress = [&](Event* e) {
        float mag = 0.01f;
        if (e->key.action == Event::ACTION::REPEAT||Event::ACTION::PRESS){
        switch (e->key.key) {
        case GLFW_KEY_A: {
            camera.moveLeft(mag);
        }
                       break;
        case GLFW_KEY_D: {
            camera.moveRight(mag);
        }
                       break;
        case GLFW_KEY_W: {
            camera.moveUp(mag);
        }
                       break;
        case GLFW_KEY_S: {
            camera.moveDown(mag);
        }
                       break;
    
        case GLFW_KEY_UP: camera.rotY(mag * 10);
                          break;
        case GLFW_KEY_DOWN: camera.rotY(-mag * 10);
                          break;
        case GLFW_KEY_LEFT: camera.rotX(mag * 10);
                          break;
        case GLFW_KEY_RIGHT: camera.rotX(-mag * 10);
                           break;
        case GLFW_KEY_SPACE:space = true;
        }
      shader.setUniform("View", camera.getView());
                
        }
    };
    win->event.onScroll = [&](Event* e) {
        double y = e->mouse.sc.y;
        float mag = 0.1f;
        if (y < 0)
            camera.moveAhead(mag);
        else
            camera.moveBack(mag);
        shader.setUniform("View", camera.getView());
    };
    
  
    shader.setUniform("Projection", Transform::Prospective(70.0f, 800.0f / 600.0f, 0.1f, 100.0f));
    shader.setUniform("View", camera.getView());
    
    win->InitEvents();
    dbuf.Done();
    while(win->isOpen()){
       win->ClearColor(BGL::Color::BLACK);
       dbuf.Draw();
       pbuf.Loop();
       for (unsigned int id : did) {
           dl[id].update();
           dbuf.updDrawable(id);
       }
       g_fps++;
       win->Update();
    }
    
    isOpen = false;
	win->Close();
    fp.join();

    Window::CloseAll();
    std::cout << "Duration : " << a.Curr() << "ms\n";
    std::cin.get();
    return 0;
}
#endif
