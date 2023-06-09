#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "Classes/Geometry/Geometry.hpp"

#include "Classes/Base/Application.hpp"

#include <time.h>

const int screenWidth = 1920;
const int screenHeight = 1080;
const char* screenTitle = "RGB Lines Test";

#define MOVE_RIGHT GLFW_KEY_D
#define MOVE_LEFT GLFW_KEY_A
#define MOVE_UP GLFW_KEY_W
#define MOVE_DOWN GLFW_KEY_S

#define ROTATE_PLUS GLFW_KEY_RIGHT
#define ROTATE_MINUS GLFW_KEY_LEFT

class RGBApplication : public Application
{
protected:
    RGBApplication(const std::string& winTitle, int width, int height)
        :Application(winTitle, width, height)
    {
        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* win, int width, int height){
            Application::CurrentApplication()->SetWidth(width);
            Application::CurrentApplication()->SetHeight(height);
        });
    }
    
    void window_size_callback(GLFWwindow* win, int width, int height)
    {
        m_winWidth = width;
        m_winHeight = height;
    }

public:
    static RGBApplication* CreateApplication(const std::string& winTitle, int width, int height)
    {
        RGBApplication* app = new RGBApplication(winTitle, width, height);
        if (m_currApp != nullptr)
            m_currApp->FreeApplication();
        
        Application::m_currApp = app;
        return app;
    }

    void Main() override
    {
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        Oval* moval = Oval::Create(50, 10, 0, 0);
        Rectangle* rect = Rectangle::Create();

        int moval_speed_x = 500;
        int moval_speed_y = 500;

        int rotatespeed = 360;

        double _prev_time = glfwGetTime();
        double _curr_time = glfwGetTime();
        double deltatime = 0;


        while (!glfwWindowShouldClose(m_window))
        {
            _prev_time = _curr_time;
            _curr_time = glfwGetTime();
            deltatime = _curr_time - _prev_time;

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (glfwGetKey(m_window, MOVE_DOWN) == GLFW_PRESS)
                moval->SetY(moval->GetCenterY() - moval_speed_y * deltatime);
            if (glfwGetKey(m_window, MOVE_UP) == GLFW_PRESS)
                moval->SetY(moval->GetCenterY() + moval_speed_y * deltatime);
            if (glfwGetKey(m_window, MOVE_RIGHT) == GLFW_PRESS)
                moval->SetX(moval->GetCenterX() + moval_speed_x * deltatime);
            if (glfwGetKey(m_window, MOVE_LEFT) == GLFW_PRESS)
                moval->SetX(moval->GetCenterX() - moval_speed_x * deltatime);

            if (glfwGetKey(m_window, ROTATE_PLUS) == GLFW_PRESS)
                moval->SetAngle(moval->GetAngle() + rotatespeed * deltatime);
            if (glfwGetKey(m_window, ROTATE_MINUS) == GLFW_PRESS)
                moval->SetAngle(moval->GetAngle() - rotatespeed * deltatime);
            
            if (moval->GetAngle() >= 360)
                moval->SetAngle(moval->GetAngle() - 360);
            else if (moval->GetAngle() < 0)
                moval->SetAngle(moval->GetAngle() + 360);

            Objects::Update(deltatime);
            Objects::Render();

            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }

        Objects::DeleteAll();
    }
};

int main()
{
    srand(time(0));

    if (!glfwInit())
    {
        std::cout << "Could not init GLFW." << std::endl;
        const char** ptr; glfwGetError(ptr);
        std::cout << ptr << std::endl;
        return -1;
    }

    // windowhints
    glfwWindowHint(GLFW_SAMPLES, 8);

    RGBApplication* App = RGBApplication::CreateApplication(screenTitle, screenWidth, screenHeight);
    App->Main();
    App->FreeApplication();

    glfwTerminate();
}