#ifndef __MIRROR_H__
#define __MIRROR_H__

#include "ModelBase.h"

class Mirror : public ModelBase {
   public:
    glm::vec3 center;
    float width;
    float height;

    Mirror(glm::vec3 center, float width, float height, glm::vec3 normal, std::shared_ptr<MaterialBase> mat);

    glm::vec3 get_surface_point() override;

   private:
    glm::vec3 normal, tangent, bitangent;
};

#endif