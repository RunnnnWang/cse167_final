#include "GeomSphere.h"

#include <iostream>
#include <utility>

#include "Intersection.h"
#include "Ray.h"

std::vector<Intersection> GeomSphere::intersect(Ray &ray) {
    /**
     * NOTE: Ray is already transformed to the Model coordinate space.
     */
    using namespace glm;

    // vector to store the intersections
    std::vector<Intersection> intersections;

    /**
     * TODO: Implement the Ray intersection with the current geometry
     */
    const vec3 &origin = ray.p0;
    const vec3 &dir = ray.dir;
    
    // Sphere is centered at origin in model space
    const vec3 center(0.0f, 0.0f, 0.0f);
    
    // Vector from sphere center to ray origin
    vec3 oc = origin - center;
    
    // Coefficients for quadratic equation: at² + bt + c = 0
    float a = dot(dir, dir);                  // a = ||dir||²
    float b = 2.0f * dot(dir, oc);            // b = 2(dir · oc)
    float c = dot(oc, oc) - radius * radius;  // c = ||oc||² - R²
    
    // Calculate discriminant
    float discriminant = b * b - 4.0f * a * c;
    
    // If discriminant is negative, no intersection
    if (discriminant < 0.0f) {
        return intersections;
    }

    float sqrtDiscriminant = sqrt(discriminant);
    
    // Calculate the two intersection points
    float t1 = (-b - sqrtDiscriminant) / (2.0f * a);
    float t2 = (-b + sqrtDiscriminant) / (2.0f * a);
    
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
    if (t1 > 0.0f) {
        vec3 point = origin + t1 * dir;
        vec3 normal = normalize(point - center);
        intersections.push_back({t1, point, normal, this, nullptr});
    }
    
    // Second intersection point (if valid and different from first)
    if (t2 > 0.0f && fabs(t2 - t1) > 1e-4f) {
        vec3 point = origin + t2 * dir;
        vec3 normal = normalize(point - center);
        intersections.push_back({t2, point, normal, this, nullptr});
    }
    
    

    return intersections;
};