//
// Created by cauchywei on 2017/8/20.
//

#ifndef SHIBA_SHADERPROGRAM_H
#define SHIBA_SHADERPROGRAM_H

#include "../../ShibaOpenGL.h"
#include <vector>
#include <map>
#include <string>

namespace shiba {
    namespace framework {
        namespace graphic {
            namespace shader {

                GLuint loadProgram(const std::string &vertexShaderFile, const std::string &fragmentShaderFile);

                class ShaderProgram {
                public:
                    ShaderProgram(const std::string &vertexShaderSrc, const std::string &fragmentShaderSrc);

                    void initialize();

                    void release();

                    GLuint id;
                protected:
                    std::string vertexShaderSrc;
                    std::string fragmentShaderSrc;
                };
            }
        }
    }
}


#endif //SHIBA_SHADERPROGRAM_H
