//
// Created by Asandei Stefan on 07.08.2023.
//

#pragma once

#include "core/base.h"
#include "core/window.h"

#include "gfx/wgpu_context.h"

namespace sakura {
    class MainRenderer {
    public:
        MainRenderer(MainRenderer const&) = delete;
        MainRenderer& operator=(MainRenderer const&) = delete;

        static Ref<MainRenderer> GetInstance(const Ref<Window>& window) {
            static std::shared_ptr<MainRenderer> s{new MainRenderer(window)};
            return s;
        }

    public:
        void Draw();
        void Destroy();

    private:
        explicit MainRenderer(const Ref<Window>& window);

        WGPUContext* m_Context;

        Ref<wgpu::SwapChain> m_SwapChain;
    };
}