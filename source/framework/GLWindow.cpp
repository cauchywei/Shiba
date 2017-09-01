//
// Created by cauchywei on 2017/8/20.
//

#include "GLWindow.h"
#include "../Application.h"
#include "model/Model.h"
#include "model/loader/ModelLoader.h"
#include "ShibaOpenGL.h"
#include "math/matrix.h"
#include "graphic/shader/ShaderProgram.h"
#include "../utils/FileUtil.h"
#include <cmath>

namespace shiba {
    namespace framework {


        using namespace shiba::framework::model;
        using namespace shiba::framework::graphic::shader;
        using namespace std;

        class GLWindowRenderer : public GLRenderer {
        public:
            GLWindowRenderer(GLWindow *hostWindow) : GLRenderer(hostWindow) {
            }

            ~GLWindowRenderer() override = default;

        protected:
            void run() override {

                hostWindow->attachGL();
                glViewport(0, 0, hostWindow->getNativeWindow()->getWidth(),
                           hostWindow->getNativeWindow()->getHeight());
                double delta = 0;
                double speed = 0.01;

                Model *model = load((char *) "bunny", (char *) "resource/bunny.obj");


                GLuint vao;
                glGenVertexArrays(1, &vao);
                check_gl_error();

                glBindVertexArray(vao);
                check_gl_error();

                GLuint indexBufferId;
                glGenBuffers(1, &indexBufferId);
                check_gl_error();

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
                check_gl_error();

                GLuint indicesCount = model->indices.size();
                glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                             indicesCount * sizeof(model->indices[0]),
                             &model->indices[0],
                             GL_STATIC_DRAW);
                check_gl_error();

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


                unsigned long pCount = model->vertices.size() * 3 * 2;
                float *p = new float[pCount];
                int offset = 0;
                for (int i = 0; i < model->vertices.size(); ++i) {
                    auto &vertex = model->vertices[i];
                    p[offset] = vertex.x;
                    p[offset + 1] = vertex.y;
                    p[offset + 2] = vertex.z;
                    auto &normal = model->normals[i];
                    p[offset + 3] = normal.x;
                    p[offset + 4] = normal.y;
                    p[offset + 5] = normal.z;
                    offset += 6;
                }
                GLuint vbo;
                glGenBuffers(1, &vbo);
                check_gl_error();
                glBindBuffer(GL_ARRAY_BUFFER, vbo);
                check_gl_error();
                glBufferData(GL_ARRAY_BUFFER,
                             pCount * sizeof(float),
                             p,
                             GL_STATIC_DRAW);
                check_gl_error();
                glEnableVertexAttribArray(0);
                check_gl_error();
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
                check_gl_error();

                glEnableVertexAttribArray(1);
                check_gl_error();
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void *) (3 * sizeof(float)));
                check_gl_error();


                glBindBuffer(GL_ARRAY_BUFFER, 0);
                check_gl_error();

                delete[] p;

                Matrix4 modelMatrix;
                Matrix4 transformMatrix;

                auto aspect =
                        hostWindow->getNativeWindow()->getWidth() / (float) hostWindow->getNativeWindow()->getHeight();
                const Matrix4 &projection = perspective(1, aspect, 5.f, 10000.f);
                const Matrix4 &view = lookAt({0.f, 0.f, 7.f}, {0.f, 0.f, 0.f}, {0.f, 1.f, 0.f});
                const Matrix4 &vp = projection * view;

                graphic::shader::ShaderProgram *program;
                {
                    string vertexStr;
                    string fragmentStr;
                    utils::readFile("resource/shader/normal_vertex_shader.glsl", vertexStr);
                    utils::readFile("resource/shader/normal_fragment_shader.glsl", fragmentStr);
                    program = new ShaderProgram(vertexStr, fragmentStr);
                }
                program->initialize();
                check_gl_error();


                auto vertexHandler = glGetAttribLocation(program->id, "vertex");
                check_gl_error();

                auto normalHandler = glGetAttribLocation(program->id, "normal");
                check_gl_error();

//                auto textureHandler = glGetUniformLocation(program.id, "texture");

                auto transformHandler = glGetUniformLocation(program->id, "transformMatrix");
                check_gl_error();
                auto viewHandler = glGetUniformLocation(program->id, "viewMatrix");
                check_gl_error();
                auto viewProjectionHandler = glGetUniformLocation(program->id, "projectionMatrix");
                check_gl_error();


                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
                check_gl_error();
                glUseProgram(program->id);
                check_gl_error();
                while (running) {
                    glViewport(0, 0, hostWindow->getNativeWindow()->getWidth(),
                               hostWindow->getNativeWindow()->getHeight());
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    glClearColor(1, 1, 1, 1);


                    glUniformMatrix4fv(transformHandler, 1, GL_FALSE,
                                       value_ptr(rotate(0,delta * 360, 0) * transformMatrix));
                    check_gl_error();
                    glUniformMatrix4fv(viewHandler, 1, GL_FALSE, value_ptr(view));
                    check_gl_error();
                    glUniformMatrix4fv(viewProjectionHandler, 1, GL_FALSE, value_ptr(projection));
                    check_gl_error();

                    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
                    check_gl_error();

                    hostWindow->swapSurface();

                    std::this_thread::sleep_for(std::chrono::milliseconds(30));
                    delta += speed;
                    if (delta > 1) {
                        speed = -0.01;
                    } else if (delta <= 0) {
                        speed = 0.01;
                    }
                }

                program->release();
                hostWindow->detachGL();

            }

        private:
            bool running = true;
        };


        GLWindow::GLWindow() {
            glRenderer = new GLWindowRenderer(this);
            renderingThread = new std::thread(std::ref(*glRenderer));
        }

        GLWindow::~GLWindow() {
            delete glRenderer;
            delete renderingThread;
        }

        void GLRenderer::test() {
            getAppController()->getLogService()->d("GLRenderer", "test");

        }
    }
}

