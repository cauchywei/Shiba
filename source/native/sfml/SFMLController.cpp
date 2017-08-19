//
// Created by cauchywei on 2017/8/17.
//

#include <SFML/Window.hpp>
#include <iostream>
#include "SFMLController.h"
#include "../../utils/List.h"
#include "service/SfmlLogService.h"

namespace shiba {
    namespace native {
        namespace sfml {

            using namespace sf;


            class SFMLWindow : public ISFMLWindow, public INativeWindow {
            public:
                SFMLWindow() {
                    sf::ContextSettings settings;
                    settings.depthBits = 24;
                    settings.stencilBits = 8;
                    settings.antialiasingLevel = 4;
                    settings.majorVersion = 3;
                    settings.minorVersion = 0;
                    sfWindow = new sf::Window(sf::VideoMode(1920, 1280), "Shiba", sf::Style::Default, settings);
                    sfWindow->setVisible(false);
                }

                bool isOpen() override {
                    return sfWindow->isOpen();
                }

                void close() override {
                    sfWindow->close();
                }

                int getWidth() override {
                    return sfWindow->getSize().x;
                }

                int getHeight() override {
                    return sfWindow->getSize().y;
                }

                void show() override {
                    sfWindow->setVisible(true);
                }

                bool pollEvent(sf::Event &event) {
                    return sfWindow->pollEvent(event);
                }

                bool handleEvent(Event &event) {
                    if (event.type == Event::EventType::Closed) {

                    }
                }

                bool addListener(INativeWindowListener *listener) override {
                    if (listeners.contains(listener)) {
                        return false;
                    } else {
                        listeners.add(listener);
                        return true;
                    }
                }

                bool removeListener(INativeWindowListener *listener) override {
                    return listeners.remove(listener);
                }

                void attachGL() override {
                    sfWindow->setActive(true);
                }

                void detachGL() override {
                    sfWindow->setActive(false);
                }

                void swapSurface() override {
                    sfWindow->display();
                }

            protected:
                sf::Window *sfWindow;
                List<INativeWindowListener *> listeners;
            };

            class SfmlEventService : public INativeEventService {

            public:
                bool addListener(INativeEventListener *listener) override {
                    if (listeners.contains(listener)) {
                        return false;
                    } else {
                        listeners.add(listener);
                        return true;
                    }
                }

                bool removeListener(INativeEventListener *listener) override {
                    return listeners.remove(listener);
                }

                ~SfmlEventService() override {

                }

                void postNativeWindowCreated(SFMLWindow *pWindow) {
                    for (auto i = 0; i < listeners.size(); i++) {
                        listeners[i]->onNativeWindowCreated(pWindow);

                    }
                }

                void postNativeWindowDestroy(SFMLWindow *pWindow) {
                    for (auto i = 0; i < listeners.size(); i++) {
                        listeners[i]->onNativeWindowDestory(pWindow);

                    }
                }

            private:
                List<INativeEventListener *> listeners;
            };

            class SFMLController : public INativeController, public INativeWindowService, public Interface {
            public:

                INativeWindow *createNativeWindow() override {
                    SFMLWindow *sfmlWindow = new SFMLWindow();
                    eventService.postNativeWindowCreated(sfmlWindow);
                    windows.add(sfmlWindow);
                    return sfmlWindow;
                }

                void destroyNativeWindow(INativeWindow *window) override {
                    SFMLWindow *sfmlWindow = dynamic_cast<SFMLWindow *>(window);
                    eventService.postNativeWindowDestroy(sfmlWindow);
                    windows.remove(sfmlWindow);
                    delete sfmlWindow;
                }

                void eventLooping() {

                    Event event;
                    sf::Clock clock;
                    while (running) {
                        sf::Time start = clock.getElapsedTime();
//                        logService.d(TAG, "Main loop start " + std::to_string(start.asMilliseconds()));
                        pollAndHandleEvent(event);
                        sf::Time elapse = (clock.getElapsedTime() - start);
//                        logService.d(TAG, "elapse " + std::to_string(elapse.asMilliseconds()));

                        if (elapse.asMicroseconds() < 16667) {
                            sf::sleep(sf::microseconds(16667 - elapse.asMicroseconds()));
                        }
                    }
                }

                void pollAndHandleEvent(Event &event) {
                    bool destroy = false;
                    for (int i = 0; i < windows.size(); ++i) {
                        SFMLWindow *&window = windows[i];
                        if (window->pollEvent(event)) {
                            bool processed = window->handleEvent(event);
                            if (event.type == Event::Closed) {
                                if (window == mainWindow) {
                                    destroy = true;
                                    break;
                                }
                            }
                        }
                    }

                    if (destroy) {
                        running = false;
                        for (int i = 0; i < windows.size(); ++i) {
                            windows[i]->close();
                            destroyNativeWindow(windows[i]);
                        }
                        return;
                    }
                }

                void run(INativeWindow *window) override {
                    mainWindow = dynamic_cast<SFMLWindow *>(window);
                    mainWindow->show();
                    eventLooping();
                }

                INativeWindowService *getWindowService() override {
                    return this;
                }

                INativeEventService *getEventService() override {
                    return &eventService;
                }

                ILogService *getLogService() override {
                    return &logService;
                }

                ~SFMLController() override {
                }

            private:
                SFMLWindow *mainWindow = nullptr;
                List<SFMLWindow *> windows;
                SfmlLogService logService;
                static std::string TAG;
            protected:
                SfmlEventService eventService;
                bool running = true;
            };

            std::string SFMLController::TAG = "SfmlController";

            INativeController *createSFMLController() {
                return new SFMLController();
            }

            void destroySFMLController(INativeController *controller) {
                delete controller;
            }

        }
    }
}

