//
// Created by Asandei Stefan on 07.08.2023.
//

#pragma once

#include <string>

#include <glfw3webgpu.h>
#include <GLFW/glfw3.h>

#include <webgpu/webgpu.hpp>

namespace Sakura {
    struct WindowDescriptor {
        std::string Name;
        int32_t Width, Height;
    };

    class Window {
    public:
        explicit Window(const WindowDescriptor& props);
        ~Window();

        void PollEvents() const;
        bool ShouldClose() const;

        wgpu::Surface GetWGPUSurface(wgpu::Instance instance) const;

    private:
        GLFWwindow* m_Handle;
    };

}

