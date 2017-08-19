//
// Created by cauchywei on 2017/8/20.
//

#ifndef SHIBA_GLWINDOW_H
#define SHIBA_GLWINDOW_H

#include "../gui/window/GuiWindow.h"
#include <thread>
#include <condition_variable>


namespace shiba {
    namespace framework {

        using namespace shiba::window;


        class GLRenderer;

        class GLWindow : public GuiWindow {

        public:
            GLWindow();

            ~GLWindow() override;


        protected:
            std::thread *renderingThread;
            GLRenderer *glRenderer;
        };

        class GLRenderer : public Interface {
        protected:

        public:
            GLRenderer(GLWindow *hostWindow) : hostWindow(hostWindow) {}
            void test();

            void operator()() {
                run();
            }

        protected:
            virtual void run() {};

        protected:
            GLWindow *hostWindow;
        };


    }
}

#endif //SHIBA_GLWINDOW_H
