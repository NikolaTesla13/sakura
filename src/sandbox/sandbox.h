//
// Created by Asandei Stefan on 07.08.2023.
//

#pragma once

#include "core/layer.h"
#include "gfx/wgpu_context.h"
#include "gfx/main_renderer.h"

class Sandbox : public Sakura::Layer {
public:
    Sandbox();
    ~Sandbox() override;

    void OnInit() override;
    void OnUpdate() override;
    void OnDestroy() override;

private:
    Sakura::Ref<Sakura::MainRenderer> m_MainRenderer;
};

