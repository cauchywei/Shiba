//
// Created by cauchywei on 2017/8/17.
//

#ifndef DCRAFT_SHIBANATIVE_H
#define DCRAFT_SHIBANATIVE_H


#include "../window/INativeWindow.h"
#include "../common/ShibaTypes.h"
#include "../utils/Interface.h"

namespace shiba {
    namespace native {

        using namespace shiba::window;

        class INativeService: public Interface {

        };

        class INativeWindowListener : public Interface {
        public:
            virtual void onClose() = 0;

            virtual void onOpen() = 0;

            virtual void onDestroy() = 0;

            virtual void onMove() = 0;

            virtual void onKeyDown() = 0;

            virtual void onKeyUp() = 0;
        };

        class INativeWindow : public shiba::Interface {
        public:
            virtual bool isOpen() = 0;

            virtual void close() = 0;

            virtual int getWidth() = 0;

            virtual int getHeight() = 0;

            virtual void show() = 0;

            virtual bool addListener(INativeWindowListener *listener) = 0;

            virtual bool removeListener(INativeWindowListener *listener) = 0;
        };

        class INativeWindowService : public INativeService, Interface {
        public:

            virtual void destroyNativeWindow(INativeWindow *window) = 0;

            virtual void run(INativeWindow *window) = 0;

            virtual INativeWindow *createNativeWindow() = 0;
        };

        class INativeEventListener {
        public:

            virtual void onNativeWindowCreated(INativeWindow *window) = 0;

            virtual void onNativeWindowDestory(INativeWindow *window) = 0;

        };

        class INativeEventService : public INativeService {
        public:

            virtual bool addListener(INativeEventListener *listener) = 0;

            virtual bool removeListener(INativeEventListener *listener) = 0;
        };

        class INativeController {
        public:
            virtual INativeWindowService *getWindowService() = 0;

            virtual INativeEventService *getEventService() = 0;
        };
    }
}


#endif //DCRAFT_SHIBANATIVE_H
