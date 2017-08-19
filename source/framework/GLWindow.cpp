//
// Created by cauchywei on 2017/8/20.
//

#include "GLWindow.h"
#include "../Application.h"
#include <GL/glew.h>

namespace shiba {
    namespace framework {


        class GLWindowRenderer : public GLRenderer {
        public:
            GLWindowRenderer(GLWindow *hostWindow) : GLRenderer(hostWindow) {
            }

            ~GLWindowRenderer() override = default;

        protected:
            void run() override {
                hostWindow->attachGL();
                double delta = 0;
                double speed = 0.01;
                while (running) {
                    glViewport(0, 0, hostWindow->getNativeWindow()->getWidth(),
                               hostWindow->getNativeWindow()->getHeight());
                    glClear(GL_COLOR_BUFFER_BIT);
                    glClearColor(delta, delta, delta, 1);

                    hostWindow->swapSurface();

                    std::this_thread::sleep_for(std::chrono::milliseconds(30));
                    delta += speed;
                    if (delta > 1) {
                        speed = -0.01;
                    } else if(delta <= 0) {
                        speed = 0.01;
                    }
                }
                hostWindow->detachGL();

            }

        private:
            bool running = true;
        };


        GLWindow::GLWindow() {
            glRenderer =  new GLWindowRenderer(this);
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

