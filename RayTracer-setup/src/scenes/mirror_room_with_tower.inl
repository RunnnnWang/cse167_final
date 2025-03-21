#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "GlossyMaterial.h"
#include "RayTracer.h"
#include "Sphere.h"
#include "Square.h"
#include "Mirror.h"

using namespace glm;

Scene* mirror_room_with_tower() {
    // Materials
    std::shared_ptr<GlossyMaterial> wall_material = std::make_shared<GlossyMaterial>(vec3(0.85f, 0.85f, 0.85f), vec3(0.0f), 0.0f);
    std::shared_ptr<GlossyMaterial> floor_material = std::make_shared<GlossyMaterial>(vec3(0.7f, 0.7f, 0.8f), vec3(0.1f), 0.1f);
    std::shared_ptr<GlossyMaterial> ceiling_material = std::make_shared<GlossyMaterial>(vec3(0.85f, 0.85f, 0.85f), vec3(0.0f), 0.0f);
    
    // Perfect mirror material - high reflectivity
    std::shared_ptr<GlossyMaterial> mirror_material = std::make_shared<GlossyMaterial>(vec3(0.0f), vec3(0.95f), 1.0f);
    
    // Colorful object materials
    std::shared_ptr<GlossyMaterial> red_material = std::make_shared<GlossyMaterial>(vec3(0.9f, 0.1f, 0.1f), vec3(0.1f), 0.2f);
    std::shared_ptr<GlossyMaterial> green_material = std::make_shared<GlossyMaterial>(vec3(0.1f, 0.9f, 0.1f), vec3(0.1f), 0.3f);
    std::shared_ptr<GlossyMaterial> blue_material = std::make_shared<GlossyMaterial>(vec3(0.1f, 0.1f, 0.9f), vec3(0.2f), 0.4f);
    
    // Light material
    std::shared_ptr<GlossyMaterial> light_material = std::make_shared<GlossyMaterial>(vec3(0.0f), vec3(0.0f), 0.0f);
    light_material->convert_to_light(vec3(1.0f), vec3(50.0f));  // White light
    
    // Create root node
    std::unique_ptr<Node> root_node = std::make_unique<Node>();
    
    // Room dimensions
    float room_width = 6.0f;
    float room_height = 4.0f;
    float room_depth = 6.0f;
    
    // Floor
    std::unique_ptr<Node> floor = std::make_unique<Node>();
    floor->model = std::make_unique<Square>(vec3(0.0f), room_width, vec3(0.0f, 1.0f, 0.0f), floor_material);
    root_node->childnodes.push_back(std::move(floor));
    root_node->childtransforms.push_back(translate(vec3(0.0f, -room_height/2.0f, 0.0f)));
    
    // Ceiling
    std::unique_ptr<Node> ceiling = std::make_unique<Node>();
    ceiling->model = std::make_unique<Square>(vec3(0.0f), room_width, vec3(0.0f, -1.0f, 0.0f), ceiling_material);
    root_node->childnodes.push_back(std::move(ceiling));
    root_node->childtransforms.push_back(translate(vec3(0.0f, room_height/2.0f, 0.0f)));
    
    // Back wall
    std::unique_ptr<Node> back_wall = std::make_unique<Node>();
    back_wall->model = std::make_unique<Square>(vec3(0.0f), room_width, vec3(0.0f, 0.0f, 1.0f), wall_material);
    root_node->childnodes.push_back(std::move(back_wall));
    root_node->childtransforms.push_back(translate(vec3(0.0f, 0.0f, -room_depth/2.0f)));
    
    // Left wall
    std::unique_ptr<Node> left_wall = std::make_unique<Node>();
    left_wall->model = std::make_unique<Square>(vec3(0.0f), room_depth, vec3(1.0f, 0.0f, 0.0f), wall_material);
    root_node->childnodes.push_back(std::move(left_wall));
    root_node->childtransforms.push_back(translate(vec3(-room_width/2.0f, 0.0f, 0.0f)));
    
    // Right wall - replaced with mirror
    std::unique_ptr<Node> right_mirror = std::make_unique<Node>();
    right_mirror->model = std::make_unique<Mirror>(vec3(0.0f), room_depth, room_height, vec3(-1.0f, 0.0f, 0.0f), mirror_material);
    root_node->childnodes.push_back(std::move(right_mirror));
    root_node->childtransforms.push_back(translate(vec3(room_width/2.0f, 0.0f, 0.0f)));
    
    // Additional smaller mirror on front wall
    std::unique_ptr<Node> front_mirror = std::make_unique<Node>();
    front_mirror->model = std::make_unique<Mirror>(vec3(0.0f), 2.0f, 2.0f, vec3(0.0f, 0.0f, -1.0f), mirror_material);
    root_node->childnodes.push_back(std::move(front_mirror));
    root_node->childtransforms.push_back(translate(vec3(0.0f, 0.0f, room_depth/2.0f - 0.01f)));
    
    // Add the tower of spheres in the center
    float height_step = 0.5f;
    int num_spheres = 6;
    
    for (int i = 0; i < num_spheres; i++) {
        std::shared_ptr<GlossyMaterial> sphere_material;
        float radius;
        
        // Alternate materials and sizes
        if (i % 3 == 0) {
            sphere_material = red_material;
            radius = 0.5f - (i * 0.05f);
        } else if (i % 3 == 1) {
            sphere_material = green_material;
            radius = 0.45f - (i * 0.04f);
        } else {
            sphere_material = blue_material;
            radius = 0.4f - (i * 0.03f);
        }
        
        std::unique_ptr<Node> sphere = std::make_unique<Node>();
        sphere->model = std::make_unique<Sphere>(radius, vec3(0.0f), sphere_material);
        root_node->childnodes.push_back(std::move(sphere));
        root_node->childtransforms.push_back(
            translate(vec3(0.0f, -room_height/2.0f + radius + (i * height_step), 0.0f))
        );
    }
    
    // Add the original spheres around the room
    std::unique_ptr<Node> red_sphere = std::make_unique<Node>();
    red_sphere->model = std::make_unique<Sphere>(0.7f, vec3(0.0f), red_material);
    root_node->childnodes.push_back(std::move(red_sphere));
    root_node->childtransforms.push_back(translate(vec3(-1.5f, -room_height/2.0f + 0.7f, 1.5f)));
    
    std::unique_ptr<Node> green_sphere = std::make_unique<Node>();
    green_sphere->model = std::make_unique<Sphere>(0.5f, vec3(0.0f), green_material);
    root_node->childnodes.push_back(std::move(green_sphere));
    root_node->childtransforms.push_back(translate(vec3(1.5f, -room_height/2.0f + 0.5f, 1.5f)));
    
    std::unique_ptr<Node> blue_sphere = std::make_unique<Node>();
    blue_sphere->model = std::make_unique<Sphere>(0.6f, vec3(0.0f), blue_material);
    root_node->childnodes.push_back(std::move(blue_sphere));
    root_node->childtransforms.push_back(translate(vec3(0.0f, -room_height/2.0f + 0.6f, -1.5f)));
    
    // Add light source (ceiling light)
    std::unique_ptr<Node> ceiling_light = std::make_unique<Node>();
    ceiling_light->model = std::make_unique<Sphere>(0.2f, vec3(0.0f), light_material);
    root_node->childnodes.push_back(std::move(ceiling_light));
    root_node->childtransforms.push_back(translate(vec3(0.0f, room_height/2.0f - 0.3f, 0.0f)));
    
    return new Scene(std::move(root_node));
}