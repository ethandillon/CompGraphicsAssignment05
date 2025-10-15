//
// Created by Ben on 12/10/2020.
//
#pragma once

#include "cs4722/x11.h"

namespace cs4722 {

    class Light {
    public:
        Color ambientLight = X11::gray50;
        Color diffuseLight = X11::white;
        Color specularLight = X11::white;

        glm::vec4 lightDirectionPosition = glm::vec4(0.0, -1.0, 0.0, 0.0);
//        bool is_directional = true;
//
//        double shininess = 20.0;
//        double specular_strength = 1.0;


    };
}