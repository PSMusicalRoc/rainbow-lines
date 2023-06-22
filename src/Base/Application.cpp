#include "Base/Application.hpp"
#include "ECS/Roc_ECS.h"

#include <iostream>

bool Application::loadedGLAD = false;
Application* Application::m_currApp = nullptr;

Application::Application(const std::string& appName, int width, int height)
    :m_winTitle(appName), m_winWidth(width), m_winHeight(height)
{
    // Initialize components
    std::cout << "Initializing Components..." << std::endl;

    Coordinator* cd = Coordinator::Get();

    cd->RegisterComponent<Transform>();
    cd->RegisterComponent<Gravity>();

    std::cout << "Initialization complete!" << std::endl;


    m_window = glfwCreateWindow(width, height, appName.c_str(), NULL, NULL);
    if (!m_window)
    {
        std::cout << "Could not initialize window." << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);

    if (!loadedGLAD)
        gladLoadGL(glfwGetProcAddress);
}