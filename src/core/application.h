//
// Created by Asandei Stefan on 07.08.2023.
//

#pragma once

#include <string>
#include <memory>
#include <vector>

#include "core/layer.h"

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
        std::vector<Layer*> m_Layers;
    };

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}
