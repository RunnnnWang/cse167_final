#include "Mirror.h"
#include <glm/gtc/random.hpp>
#include "GeomTriangle.h"

using namespace glm;

Mirror::Mirror(vec3 center, float width, float height, vec3 normal, std::shared_ptr<MaterialBase> mat) {
    this->material = mat;
    this->center = center;
    this->width = width;
    this->height = height;

    // Store the normal and make sure it's normalized
    this->normal = normalize(normal);
    
    // Compute the tangent and bitangent vectors to form a coordinate system
    // Choose a reference vector that is not parallel to normal to compute tangent
    vec3 temp = (abs(normal.y) < 0.99f) ? vec3(0, 1, 0) : vec3(1, 0, 0);
    tangent = normalize(cross(temp, normal));
    bitangent = normalize(cross(normal, tangent));
}

vec3 Mirror::get_surface_point() {
    // Generate a random point on the mirror surface
    float u = linearRand(-0.5f, 0.5f);
    float v = linearRand(-0.5f, 0.5f);
    
    vec3 samplePoint = center + u * width * tangent + v * height * bitangent;
    
    // Transform to world space if necessary
    return vec3(transformation_matrix * vec4(samplePoint, 1.0f));
}