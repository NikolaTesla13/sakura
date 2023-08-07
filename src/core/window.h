//
// Created by Asandei Stefan on 07.08.2023.
//

#pragma once

#include <string>

#include <glfw3webgpu.h>
#include <GLFW/glfw3.h>

namespace sakura {
    struct WindowDescriptor {
        std::string Name;
        int32_t Width, Height;
    };

    class Window {
    public:
        explicit Window(const WindowDescriptor& props);
        ~Window();

        void PollEvents();
        bool ShouldClose();

    private:
        GLFWwindow* m_Handle;
    };

}

