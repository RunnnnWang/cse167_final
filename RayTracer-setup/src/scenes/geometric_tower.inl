// // #define GLM_FORCE_RADIANS
// // #define GLM_ENABLE_EXPERIMENTAL
// // #include <glm/glm.hpp>
// // #include <glm/gtx/transform.hpp>

// // #include "GlossyMaterial.h"
// // #include "RayTracer.h"
// // #include "Sphere.h"
// // #include "Square.h"
// // #include "Mirror.h"

// // using namespace glm;

// // Scene* geometric_tower() {
// //     // Materials
// //     std::shared_ptr<GlossyMaterial> floor_material = std::make_shared<GlossyMaterial>(vec3(0.7f, 0.7f, 0.7f), vec3(0.1f), 0.1f);
// //     std::shared_ptr<GlossyMaterial> glossy_material = std::make_shared<GlossyMaterial>(vec3(0.5f, 0.5f, 1.0f), vec3(0.9f), 0.9f);
// //     std::shared_ptr<GlossyMaterial> red_material = std::make_shared<GlossyMaterial>(vec3(0.9f, 0.1f, 0.1f), vec3(0.1f), 0.2f);
// //     std::shared_ptr<GlossyMaterial> green_material = std::make_shared<GlossyMaterial>(vec3(0.1f, 0.9f, 0.1f), vec3(0.1f), 0.3f);
// //     std::shared_ptr<GlossyMaterial> blue_material = std::make_shared<GlossyMaterial>(vec3(0.1f, 0.1f, 0.9f), vec3(0.2f), 0.4f);
    
// //     // Light material
// //     std::shared_ptr<GlossyMaterial> light_material = std::make_shared<GlossyMaterial>(vec3(0.0f), vec3(0.0f), 0.0f);
// //     light_material->convert_to_light(vec3(1.0f), vec3(100.0f));
    
// //     // Create root node
// //     std::unique_ptr<Node> root_node = std::make_unique<Node>();

// //     // Create a ground plane
// //     std::unique_ptr<Node> ground = std::make_unique<Node>();
// //     ground->model = std::make_unique<Square>(vec3(0.0f), 20.0f, vec3(0.0f, 1.0f, 0.0f), floor_material);
// //     root_node->childnodes.push_back(std::move(ground));
// //     root_node->childtransforms.push_back(translate(vec3(0.0f, -2.0f, 0.0f)));
    
// //     // Create a tower with alternating spheres
// //     float height_step = 0.8f;
// //     int num_spheres = 10;
    
// //     for (int i = 0; i < num_spheres; i++) {
// //         std::shared_ptr<GlossyMaterial> sphere_material;
// //         float radius;
        
// //         // Alternate materials and sizes
// //         if (i % 3 == 0) {
// //             sphere_material = red_material;
// //             radius = 0.8f - (i * 0.05f);
// //         } else if (i % 3 == 1) {
// //             sphere_material = green_material;
// //             radius = 0.7f - (i * 0.04f);
// //         } 
// //         else {
// //             sphere_material = blue_material;
// //             radius = 0.6f - (i * 0.03f);
// //         }
        
// //         std::unique_ptr<Node> sphere = std::make_unique<Node>();
// //         sphere->model = std::make_unique<Sphere>(radius, vec3(0.0f), sphere_material);
// //         root_node->childnodes.push_back(std::move(sphere));
// //         root_node->childtransforms.push_back(translate(vec3(0.0f, -2.0f + radius + (i * height_step), 0.0f)));
// //     }
    
// //     // Add mirrors around the tower
// //     float mirror_distance = 3.0f;
// //     float mirror_height = 4.0f;
// //     float mirror_width = 3.0f;
    
// //     // Left mirror
// //     std::unique_ptr<Node> left_mirror = std::make_unique<Node>();
// //     left_mirror->model = std::make_unique<Mirror>(vec3(0.0f), mirror_width, mirror_height, vec3(1.0f, 0.0f, 0.0f), glossy_material);
// //     root_node->childnodes.push_back(std::move(left_mirror));
// //     root_node->childtransforms.push_back(translate(vec3(-mirror_distance, 0.0f, 0.0f)));
    
// //     // Right mirror
// //     std::unique_ptr<Node> right_mirror = std::make_unique<Node>();
// //     right_mirror->model = std::make_unique<Mirror>(vec3(0.0f), mirror_width, mirror_height, vec3(-1.0f, 0.0f, 0.0f), glossy_material);
// //     root_node->childnodes.push_back(std::move(right_mirror));
// //     root_node->childtransforms.push_back(translate(vec3(mirror_distance, 0.0f, 0.0f)));
    
// //     // Back mirror
// //     std::unique_ptr<Node> back_mirror = std::make_unique<Node>();
// //     back_mirror->model = std::make_unique<Mirror>(vec3(0.0f), mirror_width, mirror_height, vec3(0.0f, 0.0f, 1.0f), glossy_material);
// //     root_node->childnodes.push_back(std::move(back_mirror));
// //     root_node->childtransforms.push_back(translate(vec3(0.0f, 0.0f, -mirror_distance)));
    
// //     // Add lights
// //     // Main light from above
// //     std::unique_ptr<Node> main_light = std::make_unique<Node>();
// //     main_light->model = std::make_unique<Sphere>(0.5f, vec3(0.0f), light_material);
// //     root_node->childnodes.push_back(std::move(main_light));
// //     root_node->childtransforms.push_back(translate(vec3(0.0f, 6.0f, 0.0f)));
    
// //     return new Scene(std::move(root_node));
// // }
// #define GLM_FORCE_RADIANS
// #define GLM_ENABLE_EXPERIMENTAL
// #include <glm/glm.hpp>
// #include <glm/gtx/transform.hpp>

// #include "GlossyMaterial.h"
// #include "RayTracer.h"
// #include "Sphere.h"
// #include "Square.h"
// #include "Mirror.h"

// using namespace glm;

// Scene* geometric_tower() {
//     // Materials
//     std::shared_ptr<GlossyMaterial> floor_material = std::make_shared<GlossyMaterial>(vec3(0.7f, 0.7f, 0.7f), vec3(0.1f), 0.1f);
//     std::shared_ptr<GlossyMaterial> glossy_material = std::make_shared<GlossyMaterial>(vec3(0.5f, 0.5f, 1.0f), vec3(0.9f), 0.9f);
//     std::shared_ptr<GlossyMaterial> red_material = std::make_shared<GlossyMaterial>(vec3(0.9f, 0.1f, 0.1f), vec3(0.1f), 0.2f);
//     std::shared_ptr<GlossyMaterial> green_material = std::make_shared<GlossyMaterial>(vec3(0.1f, 0.9f, 0.1f), vec3(0.1f), 0.3f);
//     std::shared_ptr<GlossyMaterial> blue_material = std::make_shared<GlossyMaterial>(vec3(0.1f, 0.1f, 0.9f), vec3(0.2f), 0.4f);
    
//     // Light material
//     std::shared_ptr<GlossyMaterial> light_material = std::make_shared<GlossyMaterial>(vec3(0.0f), vec3(0.0f), 0.0f);
//     light_material->convert_to_light(vec3(1.0f), vec3(100.0f));
    
//     // Create root node
//     std::unique_ptr<Node> root_node = std::make_unique<Node>();

//     // Create a ground plane
//     std::unique_ptr<Node> ground = std::make_unique<Node>();
//     ground->model = std::make_unique<Square>(vec3(0.0f), 20.0f, vec3(0.0f, 1.0f, 0.0f), floor_material);
//     root_node->childnodes.push_back(std::move(ground));
//     root_node->childtransforms.push_back(translate(vec3(0.0f, -2.0f, 0.0f)));
    
//     // Create a tower with alternating spheres - now with smaller spheres
//     float height_step = 0.4f; // Smaller step between spheres
//     int num_spheres = 20; // More spheres to compensate for smaller size
    
//     for (int i = 0; i < num_spheres; i++) {
//         std::shared_ptr<GlossyMaterial> sphere_material;
//         float radius;
        
//         // Alternate materials and sizes - all sizes reduced
//         if (i % 3 == 0) {
//             sphere_material = red_material;
//             radius = 0.4f - (i * 0.01f); // Smaller starting radius
//         } else if (i % 3 == 1) {
//             sphere_material = green_material;
//             radius = 0.35f - (i * 0.01f);
//         } else {
//             sphere_material = blue_material;
//             radius = 0.3f - (i * 0.01f);
//         }
        
//         std::unique_ptr<Node> sphere = std::make_unique<Node>();
//         sphere->model = std::make_unique<Sphere>(radius, vec3(0.0f), sphere_material);
//         root_node->childnodes.push_back(std::move(sphere));
//         root_node->childtransforms.push_back(translate(vec3(0.0f, -2.0f + radius + (i * height_step), 0.0f)));
//     }
    
//     // Add mirrors around the tower
//     float mirror_distance = 3.0f;
//     float mirror_height = 4.0f;
//     float mirror_width = 3.0f;
    
//     // Left mirror
//     std::unique_ptr<Node> left_mirror = std::make_unique<Node>();
//     left_mirror->model = std::make_unique<Mirror>(vec3(0.0f), mirror_width, mirror_height, vec3(1.0f, 0.0f, 0.0f), glossy_material);
//     root_node->childnodes.push_back(std::move(left_mirror));
//     root_node->childtransforms.push_back(translate(vec3(-mirror_distance, 0.0f, 0.0f)));
    
//     // Right mirror
//     std::unique_ptr<Node> right_mirror = std::make_unique<Node>();
//     right_mirror->model = std::make_unique<Mirror>(vec3(0.0f), mirror_width, mirror_height, vec3(-1.0f, 0.0f, 0.0f), glossy_material);
//     root_node->childnodes.push_back(std::move(right_mirror));
//     root_node->childtransforms.push_back(translate(vec3(mirror_distance, 0.0f, 0.0f)));
    
//     // Back mirror
//     std::unique_ptr<Node> back_mirror = std::make_unique<Node>();
//     back_mirror->model = std::make_unique<Mirror>(vec3(0.0f), mirror_width, mirror_height, vec3(0.0f, 0.0f, 1.0f), glossy_material);
//     root_node->childnodes.push_back(std::move(back_mirror));
//     root_node->childtransforms.push_back(translate(vec3(0.0f, 0.0f, -mirror_distance)));
    
//     // Add lights
//     // Main light from above
//     std::unique_ptr<Node> main_light = std::make_unique<Node>();
//     main_light->model = std::make_unique<Sphere>(0.5f, vec3(0.0f), light_material);
//     root_node->childnodes.push_back(std::move(main_light));
//     root_node->childtransforms.push_back(translate(vec3(0.0f, 6.0f, 0.0f)));
    
//     return new Scene(std::move(root_node));
// }
// #define GLM_FORCE_RADIANS
// #define GLM_ENABLE_EXPERIMENTAL
// #include <glm/glm.hpp>
// #include <glm/gtx/transform.hpp>

// #include "GlossyMaterial.h"
// #include "RayTracer.h"
// #include "Sphere.h"
// #include "Square.h"
// #include "Mirror.h"

// using namespace glm;

// Scene* geometric_tower() {
//     // Materials
//     std::shared_ptr<GlossyMaterial> floor_material = std::make_shared<GlossyMaterial>(vec3(0.7f, 0.7f, 0.7f), vec3(0.1f), 0.1f);
//     std::shared_ptr<GlossyMaterial> glossy_material = std::make_shared<GlossyMaterial>(vec3(0.5f, 0.5f, 1.0f), vec3(0.9f), 0.9f);
//     std::shared_ptr<GlossyMaterial> red_material = std::make_shared<GlossyMaterial>(vec3(0.9f, 0.1f, 0.1f), vec3(0.1f), 0.2f);
//     std::shared_ptr<GlossyMaterial> green_material = std::make_shared<GlossyMaterial>(vec3(0.1f, 0.9f, 0.1f), vec3(0.1f), 0.3f);
//     std::shared_ptr<GlossyMaterial> blue_material = std::make_shared<GlossyMaterial>(vec3(0.1f, 0.1f, 0.9f), vec3(0.2f), 0.4f);
    
//     // Light material
//     std::shared_ptr<GlossyMaterial> light_material = std::make_shared<GlossyMaterial>(vec3(0.0f), vec3(0.0f), 0.0f);
//     light_material->convert_to_light(vec3(1.0f), vec3(100.0f));
    
//     // Create root node
//     std::unique_ptr<Node> root_node = std::make_unique<Node>();

//     // Create a ground plane
//     std::unique_ptr<Node> ground = std::make_unique<Node>();
//     ground->model = std::make_unique<Square>(vec3(0.0f), 20.0f, vec3(0.0f, 1.0f, 0.0f), floor_material);
//     root_node->childnodes.push_back(std::move(ground));
//     root_node->childtransforms.push_back(translate(vec3(0.0f, -2.0f, 0.0f)));
    
//     // Create a tower with just 3 spheres
//     int num_spheres = 3;
    
//     // Sphere sizes - bottom largest, top smallest
//     float sizes[3] = {0.8f, 0.6f, 0.4f};
    
//     // Materials for each sphere
//     std::shared_ptr<GlossyMaterial> materials[3] = {
//         red_material,
//         green_material,
//         blue_material
//     };
    
//     // Minimal spacing between spheres
//     float spacing = 0.01f;
    
//     // Position of the first sphere (bottom)
//     float height = -2.0f + sizes[0]; // Start at ground level + first sphere radius
    
//     // Create and position each of the 3 spheres
//     for (int i = 0; i < num_spheres; i++) {
//         float radius = sizes[i];
//         std::unique_ptr<Node> sphere = std::make_unique<Node>();
//         sphere->model = std::make_unique<Sphere>(radius, vec3(0.0f), materials[i]);
//         root_node->childnodes.push_back(std::move(sphere));
        
//         // Position sphere at current height
//         root_node->childtransforms.push_back(translate(vec3(0.0f, height, 0.0f)));
        
//         // Update height for next sphere - current sphere radius + spacing + next sphere radius
//         if (i < num_spheres - 1) {
//             height += radius + spacing + sizes[i+1];
//         }
//     }
    
//     // Add mirrors around the tower
//     float mirror_distance = 3.0f;
//     float mirror_height = 4.0f;
//     float mirror_width = 3.0f;
    
//     // Left mirror
//     std::unique_ptr<Node> left_mirror = std::make_unique<Node>();
//     left_mirror->model = std::make_unique<Mirror>(vec3(0.0f), mirror_width, mirror_height, vec3(1.0f, 0.0f, 0.0f), glossy_material);
//     root_node->childnodes.push_back(std::move(left_mirror));
//     root_node->childtransforms.push_back(translate(vec3(-mirror_distance, 0.0f, 0.0f)));
    
//     // Right mirror
//     std::unique_ptr<Node> right_mirror = std::make_unique<Node>();
//     right_mirror->model = std::make_unique<Mirror>(vec3(0.0f), mirror_width, mirror_height, vec3(-1.0f, 0.0f, 0.0f), glossy_material);
//     root_node->childnodes.push_back(std::move(right_mirror));
//     root_node->childtransforms.push_back(translate(vec3(mirror_distance, 0.0f, 0.0f)));
    
//     // Back mirror
//     std::unique_ptr<Node> back_mirror = std::make_unique<Node>();
//     back_mirror->model = std::make_unique<Mirror>(vec3(0.0f), mirror_width, mirror_height, vec3(0.0f, 0.0f, 1.0f), glossy_material);
//     root_node->childnodes.push_back(std::move(back_mirror));
//     root_node->childtransforms.push_back(translate(vec3(0.0f, 0.0f, -mirror_distance)));
    
//     // Add lights
//     // Main light from above
//     std::unique_ptr<Node> main_light = std::make_unique<Node>();
//     main_light->model = std::make_unique<Sphere>(0.5f, vec3(0.0f), light_material);
//     root_node->childnodes.push_back(std::move(main_light));
//     root_node->childtransforms.push_back(translate(vec3(0.0f, 6.0f, 0.0f)));
    
//     return new Scene(std::move(root_node));
// }

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

Scene* geometric_tower() {
    // Materials
    std::shared_ptr<GlossyMaterial> floor_material = std::make_shared<GlossyMaterial>(vec3(0.7f, 0.7f, 0.7f), vec3(0.1f), 0.1f);
    std::shared_ptr<GlossyMaterial> glossy_material = std::make_shared<GlossyMaterial>(vec3(0.5f, 0.5f, 1.0f), vec3(0.9f), 0.9f);
    std::shared_ptr<GlossyMaterial> red_material = std::make_shared<GlossyMaterial>(vec3(0.9f, 0.1f, 0.1f), vec3(0.1f), 0.2f);
    std::shared_ptr<GlossyMaterial> green_material = std::make_shared<GlossyMaterial>(vec3(0.1f, 0.9f, 0.1f), vec3(0.1f), 0.3f);
    std::shared_ptr<GlossyMaterial> blue_material = std::make_shared<GlossyMaterial>(vec3(0.1f, 0.1f, 0.9f), vec3(0.2f), 0.4f);
    
    // Light material
    std::shared_ptr<GlossyMaterial> light_material = std::make_shared<GlossyMaterial>(vec3(0.0f), vec3(0.0f), 0.0f);
    light_material->convert_to_light(vec3(1.0f), vec3(100.0f));
    
    // Create root node
    std::unique_ptr<Node> root_node = std::make_unique<Node>();

    // Create a ground plane
    std::unique_ptr<Node> ground = std::make_unique<Node>();
    ground->model = std::make_unique<Square>(vec3(0.0f), 20.0f, vec3(0.0f, 1.0f, 0.0f), floor_material);
    root_node->childnodes.push_back(std::move(ground));
    root_node->childtransforms.push_back(translate(vec3(0.0f, -2.0f, 0.0f)));
    
    // Create a tower with just 3 spheres
    int num_spheres = 3;
    
    // Sphere sizes - bottom largest, top smallest
    float sizes[3] = {0.8f, 0.6f, 0.4f};
    
    // Materials for each sphere - red, green, blue
    std::shared_ptr<GlossyMaterial> materials[3] = {
        red_material,
        green_material,
        blue_material
    };
    
    // Minimal spacing between spheres
    float spacing = 0.01f;
    
    // Position of the first sphere (bottom)
    float height = -2.0f + sizes[0]; // Start at ground level + first sphere radius
    
    // Create and position each of the 3 spheres
    for (int i = 0; i < num_spheres; i++) {
        float radius = sizes[i];
        std::unique_ptr<Node> sphere = std::make_unique<Node>();
        sphere->model = std::make_unique<Sphere>(radius, vec3(0.0f), materials[i]);
        root_node->childnodes.push_back(std::move(sphere));
        
        // Position sphere at current height
        root_node->childtransforms.push_back(translate(vec3(0.0f, height, 0.0f)));
        
        // Update height for next sphere - current sphere radius + spacing + next sphere radius
        if (i < num_spheres - 1) {
            height += radius + spacing + sizes[i+1];
        }
    }
    
    // Add mirrors around the tower
    float mirror_distance = 3.0f;
    float mirror_height = 4.0f;
    float mirror_width = 3.0f;
    
    // Left mirror
    std::unique_ptr<Node> left_mirror = std::make_unique<Node>();
    left_mirror->model = std::make_unique<Mirror>(vec3(0.0f), mirror_width, mirror_height, vec3(1.0f, 0.0f, 0.0f), glossy_material);
    root_node->childnodes.push_back(std::move(left_mirror));
    root_node->childtransforms.push_back(translate(vec3(-mirror_distance, 0.0f, 0.0f)));
    
    // Right mirror
    std::unique_ptr<Node> right_mirror = std::make_unique<Node>();
    right_mirror->model = std::make_unique<Mirror>(vec3(0.0f), mirror_width, mirror_height, vec3(-1.0f, 0.0f, 0.0f), glossy_material);
    root_node->childnodes.push_back(std::move(right_mirror));
    root_node->childtransforms.push_back(translate(vec3(mirror_distance, 0.0f, 0.0f)));
    
    // Back mirror
    std::unique_ptr<Node> back_mirror = std::make_unique<Node>();
    back_mirror->model = std::make_unique<Mirror>(vec3(0.0f), mirror_width, mirror_height, vec3(0.0f, 0.0f, 1.0f), glossy_material);
    root_node->childnodes.push_back(std::move(back_mirror));
    root_node->childtransforms.push_back(translate(vec3(0.0f, 0.0f, -mirror_distance)));
    
    // Add lights
    // Main light from above
    std::unique_ptr<Node> main_light = std::make_unique<Node>();
    main_light->model = std::make_unique<Sphere>(0.5f, vec3(0.0f), light_material);
    root_node->childnodes.push_back(std::move(main_light));
    root_node->childtransforms.push_back(translate(vec3(0.0f, 6.0f, 0.0f)));
    
    return new Scene(std::move(root_node));
}