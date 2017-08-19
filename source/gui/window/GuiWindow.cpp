//
// Created by cauchywei on 2017/8/16.
//

#include "GuiWindow.h"
#include "../../Application.h"

namespace shiba {

    namespace window {

        GuiWindow::GuiWindow() {
            auto window = getAppController()->getWindowService()->createNativeWindow();
            setNativeWindow(window);
            getApplication()->registerWindow(this);
        }

        void GuiWindow::setNativeWindow(INativeWindow *window) {
            nativeWindow = window;
        }

        INativeWindow *GuiWindow::getNativeWindow() const {
            return nativeWindow;
        }

        void GuiWindow::attachGL() {
            getNativeWindow()->attachGL();
        }

        void GuiWindow::detachGL() {
            getNativeWindow()->detachGL();

        }

        void GuiWindow::swapSurface() {
            getNativeWindow()->swapSurface();
        }


    }


}