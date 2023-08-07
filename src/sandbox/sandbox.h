//
// Created by Asandei Stefan on 07.08.2023.
//

#pragma once

#include "core/layer.h"
#include "gfx/wgpu_context.h"

class Sandbox : public sakura::Layer {
public:
    Sandbox();
    ~Sandbox() override;

    void OnInit() override;
    void OnUpdate() override;
    void OnDestroy() override;
};

