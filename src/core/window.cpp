//
// Created by Asandei Stefan on 07.08.2023.
//

#include "window.h"

namespace sakura {
    Window::Window(const WindowDescriptor& props) {
        if (!glfwInit())
            std::exit(-1);

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        m_Handle = glfwCreateWindow(props.Width, props.Height, props.Name.c_str(), nullptr, nullptr);
        if (!m_Handle) {
            glfwTerminate();
            std::exit(-1);
        }

        glfwMakeContextCurrent(m_Handle);
    }

    Window::~Window() {
        glfwDestroyWindow(m_Handle);
        glfwTerminate();
    }

    void Window::PollEvents() {
        glfwSwapBuffers(m_Handle);
        glfwPollEvents();
    }

    bool Window::ShouldClose() {
        return glfwWindowShouldClose(m_Handle);
    }
}