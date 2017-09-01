//
// Created by cauchywei on 2017/8/24.
//

#ifndef SHIBA_MATH_H
#define SHIBA_MATH_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace shiba {
    namespace framework {
        namespace matrix {
            typedef glm::vec2 Vector2;
            typedef glm::vec3 Vector3;
            typedef glm::vec4 Vector4;

            typedef glm::mat4 Matrix4;

            typedef Matrix4::type::value_type vType;
        }
    }
}
#endif //SHIBA_MATH_H
