//
// Created by Asandei Stefan on 07.08.2023.
//

#include "sandbox.h"
#include <cstdio>

Sandbox::Sandbox() {
    m_MainRenderer = Sakura::MainRenderer::GetInstance(nullptr);
}

Sandbox::~Sandbox() = default;

void Sandbox::OnInit() {
    printf("init\n");
}

void Sandbox::OnUpdate() {
    m_MainRenderer->Draw();
}

void Sandbox::OnDestroy() {
    printf("destroy\n");
}
