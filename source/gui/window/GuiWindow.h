//
// Created by cauchywei on 2017/8/16.
//

#ifndef DCRAFT_GAMEWINDOW_H
#define DCRAFT_GAMEWINDOW_H

#include "INativeWindow.h"
#include "../../platform/ShibaNative.h"

namespace shiba {

    namespace window {

        using namespace shiba::platform;

        class GuiWindow:public Interface {
        public:
            GuiWindow();

            void setNativeWindow(INativeWindow *pWindow);

            INativeWindow *getNativeWindow() const;

            void attachGL();

            void detachGL();

            void swapSurface();

        private:
            INativeWindow *nativeWindow = nullptr;
        };


        class Launcher : public GuiWindow {
        public:

        };

    }
}

#endif //DCRAFT_GAMEWINDOW_H
