//
// Created by cauchywei on 2017/8/15.
//

#include "Application.h"

namespace shiba {


    INativeController *controller = nullptr;
    Application *application;

    void setAppController(INativeController *newController) {
        controller = newController;
    }

    INativeController *getAppController() {
        return controller;
    }

    Application *getApplication(){
        return application;
    }

    void Application::run(GuiWindow *mainWindow) {

        if (!this->mainWindow) {
            this->mainWindow = mainWindow;
            INativeWindow *nativeWindow = this->mainWindow->getNativeWindow();
            getAppController()->getWindowService()->run(nativeWindow);
            this->mainWindow = nullptr;
        }

//        GuiWindow* window = windowManager.setupGameWindow();
//        const sf::Time loopingInterval = sf::milliseconds((sf::Int32) (1000 / (float) frameRate));
//        sf::Clock timer;
//        WindowEvent windowEvent;
//        while (running) {
//            auto startTime = timer.getElapsedTime();
//
////            window->draw();
////            while (window->pollEvent(windowEvent)) {
////                handleEvent(windowEvent);
////            }
//
//            auto now = timer.getElapsedTime();
//            auto elapseTime = now - startTime;
//            if (elapseTime > loopingInterval) {
//                sf::sleep(elapseTime - loopingInterval);
//            }
//        }

    }

    void Application::handleEvent(WindowEvent event) {
        if (event.type == CLOSE) {
//            windowManager.getGameWindow()->close();
//            running = false;
        }
    }

    void Application::registerWindow(GuiWindow *window) {
        windows.add(window);
    }

    void Application::unregisterWindow(GuiWindow *window) {
        windows.remove(window);
    }

    void GameApplicationInitialize() {

        {
            Application app;
            application = &app;

            GameGUIMain();

        }

    }

    auto createWindow() {

    }



}

void GameApplicationMain() {
    shiba::GameApplicationInitialize();
}