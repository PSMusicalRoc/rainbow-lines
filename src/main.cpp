#include "glad/gl.h"
#include <GLFW/glfw3.h>

#include <iostream>

#include "Classes/Oval.hpp"
#include "Classes/Rectangle.hpp"

#include <time.h>

const int screenWidth = 1920;
const int screenHeight = 1080;
const char* screenTitle = "RGB Lines Test";

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

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, screenTitle,
        NULL, NULL);
    if (!window)
    {
        std::cout << "Could not initialize window." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    glEnable(GL_MULTISAMPLE);


    /*
    ######### CREATE GL THINGS AFTER HERE ############
    */


    Rectangle* rect = Rectangle::Create();
    Oval* moval = Oval::Create(300, 60, 0, 70);

    int moval_x_dir = 1;
    int moval_y_dir = 1;
    int moval_speed_x = rand() % 10 + 5;
    int moval_speed_y = rand() % 10 + 5;

    int rotatespeed = rand() % 5;



    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        moval->SetAngle(moval->GetAngle() + rotatespeed);
        if (moval->GetAngle() >= 360)
        {
            moval->SetAngle(moval->GetAngle() - 360);
        }
        
        moval->SetX(moval->GetCenterX() + (moval_x_dir * moval_speed_x));
        if (moval->GetCenterX() > screenWidth && moval_x_dir == 1 || 
            moval->GetCenterX() < 0 && moval_x_dir == -1)
        {
            moval_x_dir *= -1;
            moval_speed_x = rand() % 10 + 5;
            rotatespeed = rand() % 5;
        }

        moval->SetY(moval->GetCenterY() + (moval_y_dir * moval_speed_y));
        if (moval->GetCenterY() > screenHeight && moval_y_dir == 1 ||
            moval->GetCenterY() < 0 && moval_y_dir == -1)
        {
            moval_y_dir *= -1;
            moval_speed_y = rand() % 10 + 5;
            rotatespeed = rand() % 5;
        }

        moval->Frame_SetVertsCorrect(screenWidth, screenHeight);
        Objects::Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Objects::DeleteAll();

    glfwDestroyWindow(window);
    glfwTerminate();
}