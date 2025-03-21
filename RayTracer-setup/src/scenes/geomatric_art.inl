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

Scene* geometric_art() {
    // Materials with varying glossiness and colors
    std::shared_ptr<GlossyMaterial> platform_material = std::make_shared<GlossyMaterial>(vec3(0.9f, 0.9f, 0.9f), vec3(0.1f), 0.1f);
    std::shared_ptr<GlossyMaterial> chrome_material = std::make_shared<GlossyMaterial>(vec3(0.8f, 0.8f, 0.8f), vec3(0.9f), 0.9f);
    std::shared_ptr<GlossyMaterial> red_material = std::make_shared<GlossyMaterial>(vec3(0.9f, 0.1f, 0.1f), vec3(0.2f), 0.4f);
    std::shared_ptr<GlossyMaterial> blue_material = std::make_shared<GlossyMaterial>(vec3(0.1f, 0.3f, 0.9f), vec3(0.3f), 0.5f);
    std::shared_ptr<GlossyMaterial> green_material = std::make_shared<GlossyMaterial>(vec3(0.1f, 0.8f, 0.3f), vec3(0.2f), 0.3f);
    std::shared_ptr<GlossyMaterial> yellow_material = std::make_shared<GlossyMaterial>(vec3(0.9f, 0.8f, 0.1f), vec3(0.4f), 0.6f);
    std::shared_ptr<GlossyMaterial> purple_material = std::make_shared<GlossyMaterial>(vec3(0.7f, 0.2f, 0.8f), vec3(0.3f), 0.5f);
    
    // Light materials
    std::shared_ptr<GlossyMaterial> main_light = std::make_shared<GlossyMaterial>(vec3(0.0f), vec3(0.0f), 0.0f);
    main_light->convert_to_light(vec3(1.0f), vec3(100.0f));
    
    std::shared_ptr<GlossyMaterial> accent_light = std::make_shared<GlossyMaterial>(vec3(0.0f), vec3(0.0f), 0.0f);
    accent_light->convert_to_light(vec3(0.9f, 0.8f, 0.7f), vec3(30.0f));

    // Create Scene Tree
    std::unique_ptr<Node> root_node = std::make_unique<Node>();

    // Create a platform
    std::unique_ptr<Node> platform = std::make_unique<Node>();
    platform->model = std::make_unique<Square>(vec3(0.0f), 14.0f, vec3(0.0f, 1.0f, 0.0f), platform_material);
    root_node->childnodes.push_back(std::move(platform));
    root_node->childtransforms.push_back(translate(vec3(0.0f, -2.0f, 0.0f)));
    
    // Create a central structure with triangles forming a tetrahedron
    vec3 tetra_base = vec3(0.0f, -1.0f, 0.0f);
    float tetra_size = 3.0f;
    vec3 v0 = tetra_base + vec3(tetra_size, 0.0f, -tetra_size/sqrt(3.0f));
    vec3 v1 = tetra_base + vec3(-tetra_size, 0.0f, -tetra_size/sqrt(3.0f));
    vec3 v2 = tetra_base + vec3(0.0f, 0.0f, 2*tetra_size/sqrt(3.0f));
    vec3 v3 = tetra_base + vec3(0.0f, 2*tetra_size, 0.0f);
    
    // Triangle 1 (base)
    std::unique_ptr<Node> tri1 = std::make_unique<Node>();
    tri1->model = std::make_unique<Triangle>(v0, v1, v2, true, red_material);
    root_node->childnodes.push_back(std::move(tri1));
    root_node->childtransforms.push_back(mat4(1.0f));
    
    // Triangle 2 (side)
    std::unique_ptr<Node> tri2 = std::make_unique<Node>();
    tri2->model = std::make_unique<Triangle>(v0, v1, v3, true, blue_material);
    root_node->childnodes.push_back(std::move(tri2));
    root_node->childtransforms.push_back(mat4(1.0f));
    
    // Triangle 3 (side)
    std::unique_ptr<Node> tri3 = std::make_unique<Node>();
    tri3->model = std::make_unique<Triangle>(v1, v2, v3, true, green_material);
    root_node->childnodes.push_back(std::move(tri3));
    root_node->childtransforms.push_back(mat4(1.0f));
    
    // Triangle 4 (side)
    std::unique_ptr<Node> tri4 = std::make_unique<Node>();
    tri4->model = std::make_unique<Triangle>(v0, v2, v3, true, yellow_material);
    root_node->childnodes.push_back(std::move(tri4));
    root_node->childtransforms.push_back(mat4(1.0f));
    
    // Create rectangular columns
    float column_height = 5.0f;
    float column_width = 0.5f;
    
    // Create column using squares arranged as a rectangular prism
    for (int i = 0; i < 3; i++) {
        float angle = (float)i * 2.0f * M_PI / 3.0f;
        float x = 5.0f * cos(angle);
        float z = 5.0f * sin(angle);
        
        // Front face
        std::unique_ptr<Node> column_front = std::make_unique<Node>();
        column_front->model = std::make_unique<Square>(vec3(0.0f), column_width, vec3(0.0f, 0.0f, 1.0f), chrome_material);
        root_node->childnodes.push_back(std::move(column_front));
        root_node->childtransforms.push_back(
            translate(vec3(x, column_height/2.0f - 2.0f, z)) * 
            rotate(angle, vec3(0.0f, 1.0f, 0.0f)) *
            scale(vec3(1.0f, column_height, 1.0f))
        );
        
        // Back face
        std::unique_ptr<Node> column_back = std::make_unique<Node>();
        column_back->model = std::make_unique<Square>(vec3(0.0f), column_width, vec3(0.0f, 0.0f, -1.0f), chrome_material);
        root_node->childnodes.push_back(std::move(column_back));
        root_node->childtransforms.push_back(
            translate(vec3(x, column_height/2.0f - 2.0f, z)) * 
            rotate(angle, vec3(0.0f, 1.0f, 0.0f)) *
            translate(vec3(0.0f, 0.0f, -column_width)) *
            scale(vec3(1.0f, column_height, 1.0f))
        );
        
        // Left face
        std::unique_ptr<Node> column_left = std::make_unique<Node>();
        column_left->model = std::make_unique<Square>(vec3(0.0f), column_width, vec3(1.0f, 0.0f, 0.0f), chrome_material);
        root_node->childnodes.push_back(std::move(column_left));
        root_node->childtransforms.push_back(
            translate(vec3(x, column_height/2.0f - 2.0f, z)) * 
            rotate(angle, vec3(0.0f, 1.0f, 0.0f)) *
            rotate(3.141592f/2.0f, vec3(0.0f, 1.0f, 0.0f)) *
            scale(vec3(1.0f, column_height, 1.0f))
        );
        
        // Right face
        std::unique_ptr<Node> column_right = std::make_unique<Node>();
        column_right->model = std::make_unique<Square>(vec3(0.0f), column_width, vec3(-1.0f, 0.0f, 0.0f), chrome_material);
        root_node->childnodes.push_back(std::move(column_right));
        root_node->childtransforms.push_back(
            translate(vec3(x, column_height/2.0f - 2.0f, z)) * 
            rotate(angle, vec3(0.0f, 1.0f, 0.0f)) *
            rotate(3.141592f/2.0f, vec3(0.0f, 1.0f, 0.0f)) *
            translate(vec3(0.0f, 0.0f, -column_width)) *
            scale(vec3(1.0f, column_height, 1.0f))
        );
    }
    
    // Create an arch made of triangles
    float arch_size = 3.0f;
    vec3 arch_center = vec3(-3.0f, -1.5f, -3.0f);
    
    // Arch triangles
    std::unique_ptr<Node> arch_left = std::make_unique<Node>();
    arch_left->model = std::make_unique<Triangle>(
        arch_center + vec3(-arch_size/2.0f, 0.0f, 0.0f),
        arch_center + vec3(-arch_size/2.0f, arch_size, 0.0f),
        arch_center + vec3(0.0f, arch_size*1.5f, 0.0f),
        true, purple_material
    );
    root_node->childnodes.push_back(std::move(arch_left));
    root_node->childtransforms.push_back(mat4(1.0f));
    
    std::unique_ptr<Node> arch_right = std::make_unique<Node>();
    arch_right->model = std::make_unique<Triangle>(
        arch_center + vec3(arch_size/2.0f, 0.0f, 0.0f),
        arch_center + vec3(arch_size/2.0f, arch_size, 0.0f),
        arch_center + vec3(0.0f, arch_size*1.5f, 0.0f),
        true, purple_material
    );
    root_node->childnodes.push_back(std::move(arch_right));
    root_node->childtransforms.push_back(mat4(1.0f));
    
    // Add decorative spheres on top of columns
    for (int i = 0; i < 3; i++) {
        float angle = (float)i * 2.0f * M_PI / 3.0f;
        float x = 5.0f * cos(angle);
        float z = 5.0f * sin(angle);
        
        std::unique_ptr<Node> top_sphere = std::make_unique<Node>();
        top_sphere->model = std::make_unique<Sphere>(0.5f, vec3(0.0f), red_material);
        root_node->childnodes.push_back(std::move(top_sphere));
        root_node->childtransforms.push_back(translate(vec3(x, column_height - 1.5f, z)));
    }
    
    // Add a disc of small spheres around the tetrahedron
    int num_ring_spheres = 8;
    float ring_radius = 4.0f;
    for (int i = 0; i < num_ring_spheres; i++) {
        float angle = (float)i * 2.0f * M_PI / num_ring_spheres;
        float x = ring_radius * cos(angle);
        float z = ring_radius * sin(angle);
        
        std::shared_ptr<GlossyMaterial> sphere_material;
        switch (i % 4) {
            case 0: sphere_material = red_material; break;
            case 1: sphere_material = blue_material; break;
            case 2: sphere_material = green_material; break;
            case 3: sphere_material = yellow_material; break;
        }
        
        std::unique_ptr<Node> ring_sphere = std::make_unique<Node>();
        ring_sphere->model = std::make_unique<Sphere>(0.4f, vec3(0.0f), sphere_material);
        root_node->childnodes.push_back(std::move(ring_sphere));
        root_node->childtransforms.push_back(translate(vec3(x, -1.5f, z)));
    }
    
    // Add lights
    std::unique_ptr<Node> primary_light = std::make_unique<Node>();
    primary_light->model = std::make_unique<Sphere>(0.5f, vec3(0.0f), main_light);
    root_node->childnodes.push_back(std::move(primary_light));
    root_node->childtransforms.push_back(translate(vec3(10.0f, 10.0f, 5.0f)));
    
    std::unique_ptr<Node> secondary_light = std::make_unique<Node>();
    secondary_light->model = std::make_unique<Sphere>(0.3f, vec3(0.0f), accent_light);
    root_node->childnodes.push_back(std::move(secondary_light));
    root_node->childtransforms.push_back(translate(vec3(-8.0f, 5.0f, -8.0f)));

    return new Scene(std::move(root_node));
}