//
// Created by cauchywei on 2017/8/20.
//

#ifndef SHIBA_MESH_H
#define SHIBA_MESH_H

#include <vector>
#include "../math/math.h"

namespace shiba {
    namespace framework {
        namespace model {

            using namespace shiba::framework::matrix;

            struct Mesh {
                std::vector<Vector3> vertices;
                std::vector<Vector3> normals;
                std::vector<Vector3> textures;
                std::vector<uint32_t> indices;
            };
        }
    }
}

#endif //SHIBA_MESH_H
