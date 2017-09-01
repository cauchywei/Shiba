//
// Created by cauchywei on 2017/8/25.
//

#ifndef SHIBA_MATRIX_H
#define SHIBA_MATRIX_H

#include "math.h"

namespace shiba {
    namespace framework {
        namespace matrix {

            Matrix4 rotate(float x, float y, float z) {
                Matrix4 matrix;
                matrix = glm::rotate(matrix, glm::radians(x), {1, 0, 0});
                matrix = glm::rotate(matrix, glm::radians(y), {0, 1, 0});
                matrix = glm::rotate(matrix, glm::radians(z), {0, 0, 1});
                return matrix;
            }

            Matrix4 perspective(float fovy, float aspect, float near, float far) {
                return glm::perspective(fovy, aspect, near, far);
            }

            Matrix4 lookAt(Vector3 const &eye, Vector3 const &center, Vector3 const &up) {
                return glm::lookAt(eye, center, up);
            }

            vType *value_ptr(Matrix4 &matrix4) {
                return glm::value_ptr(matrix4);
            }
        }
    }
}

#endif //SHIBA_MATRIX_H
