//
// Created by cauchywei on 2017/8/20.
//

#include <iostream>
#include "ShaderProgram.h"
#include "../../../utils/FileUtil.h"
#include "../../../Application.h"

namespace shiba {
    namespace framework {
        namespace graphic {

            namespace shader {
                bool checkCompiled(GLuint id);

                GLuint compileShader(const GLchar *source, GLenum type) {
                    auto id = glCreateShader(type);
                    check_gl_error();

                    glShaderSource(id, 1, &source, nullptr);
                    check_gl_error();

                    glCompileShader(id);
                    if(!checkCompiled(id)) {
                        return 0;
                    }

                    GLint isSuccess;
                    GLchar infoLog[512];

                    glGetShaderiv(id, GL_COMPILE_STATUS, &isSuccess);
                    check_gl_error();

                    if (!isSuccess) {
                        glGetShaderInfoLog(id, 512, nullptr, infoLog);
                        throw std::runtime_error("Error compiling shader: " + std::string(infoLog));
                    }

                    return id;
                }

                bool checkCompiled(GLuint id) {
                    int compiled;
                    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
                    if (compiled == GL_FALSE) {
                        GLint maxLength = 0;
                        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

                        // The maxLength includes the NULL character
                        std::__1::vector<GLchar> errorLog(maxLength);
                        glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

                        // Provide the infolog in whatever manor you deem best.
                        // Exit with failure.
                        glDeleteShader(id); // Don't leak the shader.
                        getAppController()->getLogService()->e("GL", "Compilation Failed" +
                                                                     std::string(errorLog.begin(), errorLog.end()));
                    }
                    return compiled == GL_TRUE;
                }


                GLuint createProgram(GLuint vertexShaderID, GLuint fragmentShaderID) {
                    auto id = glCreateProgram();
                    check_gl_error();
                    glAttachShader(id, vertexShaderID);
                    check_gl_error();
                    glAttachShader(id, fragmentShaderID);
                    check_gl_error();
                    glLinkProgram(id);
                    check_gl_error();

                    glDetachShader(id, vertexShaderID);
                    glDetachShader(id, fragmentShaderID);

                    glDeleteShader(vertexShaderID);
                    glDeleteShader(fragmentShaderID);

                    return id;
                }

                GLuint loadProgram(const std::string &vertexShaderSrc, const std::string &fragmentShaderSrc) {

                    auto vertexShaderID = compileShader(vertexShaderSrc.c_str(), GL_VERTEX_SHADER);
                    check_gl_error();
                    auto fragmentShaderID = compileShader(fragmentShaderSrc.c_str(), GL_FRAGMENT_SHADER);
                    check_gl_error();

                    auto programID = createProgram(vertexShaderID, fragmentShaderID);

                    return programID;
                }


                ShaderProgram::ShaderProgram(const std::string &vertexShaderSrc, const std::string &fragmentShaderSrc)
                        : vertexShaderSrc(vertexShaderSrc), fragmentShaderSrc(fragmentShaderSrc) {}

                void ShaderProgram::initialize() {
                    id = loadProgram(vertexShaderSrc, fragmentShaderSrc);
                }

                void ShaderProgram::release() {
                    glDeleteProgram(id);
                    id = 0;
                }

            }
        }
    }
}