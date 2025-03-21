#include "Triangle.h"
#include <glm/gtc/random.hpp>

using namespace glm;

Triangle::Triangle(vec3 v0, vec3 v1, vec3 v2, std::shared_ptr<MaterialBase> mat) {
    this->material = mat;
    this->v0 = v0;
    this->v1 = v1;
    this->v2 = v2;
    
    // Calculate face normal using cross product
    vec3 edge1 = v1 - v0;
    vec3 edge2 = v2 - v0;
    this->normal = normalize(cross(edge1, edge2));
}

Triangle::Triangle(vec3 v0, vec3 v1, vec3 v2, bool calculateNormal, std::shared_ptr<MaterialBase> mat) {
    this->material = mat;
    this->v0 = v0;
    this->v1 = v1;
    this->v2 = v2;
    
    if (calculateNormal) {
        // Calculate face normal using cross product
        vec3 edge1 = v1 - v0;
        vec3 edge2 = v2 - v0;
        this->normal = normalize(cross(edge1, edge2));
    } else {
        this->normal = vec3(0.0f, 1.0f, 0.0f); // Default up
    }
}

vec3 Triangle::get_surface_point() {
    // Generate random barycentric coordinates
    float u = linearRand(0.0f, 1.0f);
    float v = linearRand(0.0f, 1.0f - u);
    float w = 1.0f - u - v;
    
    // Compute the point using barycentric coordinates
    vec3 point = u * v0 + v * v1 + w * v2;
    
    // Transform to world space if necessary
    return vec3(transformation_matrix * vec4(point, 1.0f));
}