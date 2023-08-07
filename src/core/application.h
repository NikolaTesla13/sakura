//
// Created by Asandei Stefan on 07.08.2023.
//

#pragma once

#include <string>
#include <vector>

#include "core/window.h"
#include "core/layer.h"
#include "core/base.h"

#include "gfx/wgpu_context.h"

namespace sakura {
    struct ApplicationDescriptor {
        int32_t Width, Height;
        std::string Name;
    };

    class Application {
    public:
        explicit Application(const ApplicationDescriptor& desc);
        ~Application();

        void PushLayer(Layer* layer);
        int32_t Run();

    private:
        Ref<Window> m_Window;
        WGPUContext* m_Context;

        std::vector<Layer*> m_Layers;
    };
}
