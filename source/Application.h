//
// Created by cauchywei on 2017/8/15.
//

#ifndef DCRAFT_APPLICATION_H
#define DCRAFT_APPLICATION_H

#include "gui/window/GuiWindow.h"
#include "native/ShibaNative.h"
#include "utils/List.h"
#include "gui/window/WindowEvent.h"

extern void GameGUIMain();


namespace shiba {

    using namespace shiba::native;
    using namespace shiba::window;

    class Application {
    public:
        void run(GuiWindow *mainWindow);

        static Application &instance() {
            static Application application;
            return application;
        }

        std::string &getApplicationName() {
            return name;
        }

        void registerWindow(GuiWindow *pWindow);

        void unregisterWindow(GuiWindow *pWindow);

    private:
        std::string name = "DCraft";
        GuiWindow *mainWindow = nullptr;
        List<GuiWindow *> windows;

        void handleEvent(WindowEvent event);
    };

    extern void setAppController(INativeController *newController);

    extern INativeController *getAppController();

    extern Application* getApplication();

}

extern void GameApplicationMain();

#endif //DCRAFT_APPLICATION_H
