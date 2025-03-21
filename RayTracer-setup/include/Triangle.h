#pragma once

#include <glm/glm.hpp>
#include "ModelBase.h"

class Triangle : public ModelBase {
public:
    glm::vec3 v0, v1, v2;    // Three vertices
    glm::vec3 normal;        // Face normal

    Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, std::shared_ptr<MaterialBase> mat);
    
    // Optional constructor that calculates normal automatically
    Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, bool calculateNormal, std::shared_ptr<MaterialBase> mat);
    
    glm::vec3 get_surface_point() override;
};