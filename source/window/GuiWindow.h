//
// Created by cauchywei on 2017/8/16.
//

#ifndef DCRAFT_GAMEWINDOW_H
#define DCRAFT_GAMEWINDOW_H

#include "INativeWindow.h"
#include "../native/ShibaNative.h"

namespace shiba {

    namespace window {

        using namespace shiba::native;

        class GuiWindow {
        public:
            GuiWindow();

            void setNativeWindow(INativeWindow *pWindow);


            INativeWindow *getNativeWindow() const;

        private:
            INativeWindow *nativeWindow = nullptr;
        };


        class Launcher : public GuiWindow {

        };

    }
}

#endif //DCRAFT_GAMEWINDOW_H
