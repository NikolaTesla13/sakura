//
// Created by Asandei Stefan on 07.08.2023.
//

#include "application.h"

namespace sakura {
    Application::Application(const sakura::ApplicationDescriptor &desc) {

    }

    Application::~Application() {

    }

    void Application::PushLayer(Layer *layer) {
        m_Layers.emplace_back(layer);
    }

    int32_t Application::Run() {
        for(auto layer : m_Layers)
            layer->OnInit();

        for(auto layer : m_Layers) {
            layer->OnDestroy();
            delete layer;
        }

        return EXIT_SUCCESS;
    }
}