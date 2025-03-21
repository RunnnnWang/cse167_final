#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "GlossyMaterial.h"
#include "RayTracer.h"
#include "Sphere.h"
#include "Square.h"
#include "Triangle.h"

using namespace glm;

Scene* abstract_sculpture() {
    // Materials
    std::shared_ptr<GlossyMaterial> platform_material = std::make_shared<GlossyMaterial>(vec3(0.8f, 0.8f, 0.9f), vec3(0.05f), 0.2f);
    std::shared_ptr<GlossyMaterial> blue_metal = std::make_shared<GlossyMaterial>(vec3(0.2f, 0.3f, 0.8f), vec3(0.6f), 0.8f);
    std::shared_ptr<GlossyMaterial> gold_metal = std::make_shared<GlossyMaterial>(vec3(0.8f, 0.7f, 0.2f), vec3(0.8f), 0.7f);
    std::shared_ptr<GlossyMaterial> red_glass = std::make_shared<GlossyMaterial>(vec3(0.9f, 0.1f, 0.1f), vec3(0.4f), 0.95f);
    std::shared_ptr<GlossyMaterial> green_matte = std::make_shared<GlossyMaterial>(vec3(0.1f, 0.8f, 0.3f), vec3(0.0f), 0.1f);
    
    // Light materials
    std::shared_ptr<GlossyMaterial> white_light = std::make_shared<GlossyMaterial>(vec3(0.0f), vec3(0.0f), 0.0f);
    white_light->convert_to_light(vec3(1.0f), vec3(80.0f));
    
    std::shared_ptr<GlossyMaterial> blue_light = std::make_shared<GlossyMaterial>(vec3(0.0f), vec3(0.0f), 0.0f);
    blue_light->convert_to_light(vec3(0.5f, 0.5f, 1.0f), vec3(20.0f));

    // Create Scene Tree
    std::unique_ptr<Node> root_node = std::make_unique<Node>();

    // Create a platform
    std::unique_ptr<Node> platform = std::make_unique<Node>();
    platform->model = std::make_unique<Square>(vec3(0.0f), 10.0f, vec3(0.0f, 1.0f, 0.0f), platform_material);
    root_node->childnodes.push_back(std::move(platform));
    root_node->childtransforms.push_back(translate(vec3(0.0f, -2.0f, 0.0f)));
    
    // Create a pyramid of spheres
    float sphere_size = 1.0f;
    float spacing = 2.5f * sphere_size;
    
    // Base spheres in a square
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            std::unique_ptr<Node> base_sphere = std::make_unique<Node>();
            float x = (i - 0.5f) * spacing;
            float z = (j - 0.5f) * spacing;
            base_sphere->model = std::make_unique<Sphere>(sphere_size, vec3(0.0f), blue_metal);
            root_node->childnodes.push_back(std::move(base_sphere));
            root_node->childtransforms.push_back(translate(vec3(x, -1.0f, z)));
        }
    }
    
    // Middle sphere
    std::unique_ptr<Node> middle_sphere = std::make_unique<Node>();
    middle_sphere->model = std::make_unique<Sphere>(sphere_size * 0.8f, vec3(0.0f), gold_metal);
    root_node->childnodes.push_back(std::move(middle_sphere));
    root_node->childtransforms.push_back(translate(vec3(0.0f, 0.5f, 0.0f)));
    
    // Top sphere
    std::unique_ptr<Node> top_sphere = std::make_unique<Node>();
    top_sphere->model = std::make_unique<Sphere>(sphere_size * 0.6f, vec3(0.0f), red_glass);
    root_node->childnodes.push_back(std::move(top_sphere));
    root_node->childtransforms.push_back(translate(vec3(0.0f, 1.8f, 0.0f)));
    
    // Create triangular fins around the structure
    float fin_height = 4.0f;
    float fin_width = 3.0f;
    int num_fins = 3;
    
    for (int i = 0; i < num_fins; i++) {
        float angle = (float)i * 2.0f * M_PI / num_fins;
        float next_angle = (float)(i + 1) * 2.0f * M_PI / num_fins;
        
        vec3 base_center = vec3(0.0f, -2.0f, 0.0f);
        vec3 fin_tip = base_center + vec3(0.0f, fin_height, 0.0f);
        
        vec3 dir1 = vec3(cos(angle), 0.0f, sin(angle)) * fin_width;
        vec3 dir2 = vec3(cos(next_angle), 0.0f, sin(next_angle)) * fin_width;
        
        vec3 v0 = base_center + dir1;
        vec3 v1 = base_center + dir2;
        vec3 v2 = fin_tip;
        
        std::unique_ptr<Node> fin = std::make_unique<Node>();
        fin->model = std::make_unique<Triangle>(v0, v1, v2, true, green_matte);
        root_node->childnodes.push_back(std::move(fin));
        root_node->childtransforms.push_back(mat4(1.0f)); // Identity transform
    }
    
    // Add decorative small spheres along one of the fins
    for (int i = 0; i < 5; i++) {
        float t = (float)i / 4.0f; // Parameter from 0 to 1
        vec3 pos = mix(vec3(fin_width, -2.0f, 0.0f), vec3(0.0f, 2.0f, 0.0f), t);
        
        float small_sphere_size = 0.2f;
        std::unique_ptr<Node> small_sphere = std::make_unique<Node>();
        small_sphere->model = std::make_unique<Sphere>(small_sphere_size, vec3(0.0f), gold_metal);
        root_node->childnodes.push_back(std::move(small_sphere));
        root_node->childtransforms.push_back(translate(pos));
    }
    
    // Add a main light source
    std::unique_ptr<Node> main_light = std::make_unique<Node>();
    main_light->model = std::make_unique<Sphere>(0.5f, vec3(0.0f), white_light);
    root_node->childnodes.push_back(std::move(main_light));
    root_node->childtransforms.push_back(translate(vec3(5.0f, 8.0f, 5.0f)));
    
    // Add an accent light
    std::unique_ptr<Node> accent_light = std::make_unique<Node>();
    accent_light->model = std::make_unique<Sphere>(0.3f, vec3(0.0f), blue_light);
    root_node->childnodes.push_back(std::move(accent_light));
    root_node->childtransforms.push_back(translate(vec3(-3.0f, 1.0f, -5.0f)));

    return new Scene(std::move(root_node));
}