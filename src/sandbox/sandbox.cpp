//
// Created by Asandei Stefan on 07.08.2023.
//

#include "sandbox.h"

#include <cstdio>

Sandbox::Sandbox() = default;

Sandbox::~Sandbox() = default;

void Sandbox::OnInit() {
    printf("init\n");
}

void Sandbox::OnUpdate() {
}

void Sandbox::OnDestroy() {
    printf("destroy\n");
}
