//
// Created by cauchywei on 2017/8/17.
//

#include <SFML/Window.hpp>
#include <jmorecfg.h>
#include "SFMLController.h"
#include "../../utils/List.h"

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
                    sfWindow = new sf::Window(sf::VideoMode(800, 600), "Shiba", sf::Style::Default, settings);
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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

                void eventLooping() {

                    Event event;
                    while (running) {

                        bool destroy = false;
                        for (int i = 0; i < windows.size(); ++i) {
                            SFMLWindow *&window = windows[i];
                            if(window->pollEvent(event)) {
                                bool processed = window->handleEvent(event);
                                if (event.type == Event::EventType::Closed) {
                                    if (window == mainWindow) {
                                        destroy = true;
                                        break;
                                    }
                                }
                            }
                        }

                        if (destroy) {
                            for (int i = 0; i < windows.size(); ++i) {
                                windows[i]->close();
                                destroyNativeWindow(windows[i]);
                            }
                            return;
                        }
                    }
                }

#pragma clang diagnostic pop

                void DispatchEvent(const Event &event) const {

                    if (event.type == Event::Closed) {

                    } else {

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

                ~SFMLController() override {
                }

            private:
                SFMLWindow *mainWindow = nullptr;
                List<SFMLWindow *> windows;
            protected:
                SfmlEventService eventService;
                bool running = true;
            };

            INativeController *createSFMLController() {
                return new SFMLController();
            }

            void destroySFMLController(INativeController *controller) {
                delete controller;
            }

        }
    }
}

