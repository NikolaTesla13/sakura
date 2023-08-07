//
// Created by Asandei Stefan on 07.08.2023.
//

#pragma once

namespace Sakura {
    class Layer {
    public:
        virtual ~Layer() = default;

        virtual void OnInit() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnDestroy() = 0;
    };
}