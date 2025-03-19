#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include "GeomTriangle.h"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "Intersection.h"
#include "Ray.h"

GeomTriangle::GeomTriangle(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals) {
    this->vertices[0] = vertices[0];
    this->vertices[1] = vertices[1];
    this->vertices[2] = vertices[2];

    this->normals[0] = normals[0];
    this->normals[1] = normals[1];
    this->normals[2] = normals[2];
}

std::vector<Intersection> GeomTriangle::intersect(Ray &ray) {
    using namespace glm;
    /**
     * NOTE: Ray is already transformed to the Model coordinate space.
     */

    // vector to store the intersections
    std::vector<Intersection> intersections;

    /**
     * TODO: Implement the Ray intersection with the current geometry
     */
    const vec3 &v0 = vertices[0];
    const vec3 &v1 = vertices[1];
    const vec3 &v2 = vertices[2];
    
    // Ray origin and direction
    const vec3 &origin = ray.p0;
    const vec3 &dir = ray.dir;
    
    // Compute edges of the triangle
    vec3 e1 = v1 - v0;
    vec3 e2 = v2 - v0;
    
    // Begin Möller–Trumbore algorithm
    vec3 h = cross(dir, e2);
    float a = dot(e1, h);
    
    // If a is too close to 0, the ray is parallel to the triangle
    const float EPSILON = 1e-8f;
    if (a > -EPSILON && a < EPSILON)
        return intersections;
    
    float f = 1.0f / a;
    vec3 s = origin - v0;
    float u = f * dot(s, h);
    
    // Check if u is out of bounds [0,1]
    if (u < 0.0f || u > 1.0f)
        return intersections;
    
    vec3 q = cross(s, e1);
    float v = f * dot(dir, q);
    
    // Check if v is out of bounds or u+v > 1
    if (v < 0.0f || u + v > 1.0f)
        return intersections;
    
    // Compute t (distance along ray)
    float t = f * dot(e2, q);

    /**
     * Once you find the intersection, add it to the `intersections` vector.
     *
     * Example:
     * Suppose the ray intersects the current geometry at a point `vec3 point`
     * at a distance `float t`, and the unit normal vector at the intersection
     * point is `vec3 normal`. You would then insert an intersection into the
     * vector as follows:
     *
     * intersections.push_back({t, point, normal, this, nullptr});
     *
     * Note:
     * - Here we pass the Model pointer as `nullptr` because it will be
     *   populated by the Model::intersect() function call.
     * - Only add intersections that are in front of the camera, i.e.,
     *   where t > 0.
     */

    /**
     * TODO: Update `intersections`
     */
    if (t > 0.0f) {
        // Calculate intersection point
        vec3 point = origin + t * dir;
        
        // Calculate barycentric coordinates
        float w = 1.0f - u - v; // Third barycentric coordinate
        
        // Interpolate normal using barycentric coordinates
        vec3 normal = normalize(w * normals[0] + u * normals[1] + v * normals[2]);
        
        // Add the intersection to the result vector
        intersections.push_back({t, point, normal, this, nullptr});
    }


    return intersections;
}