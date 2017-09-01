//
// Created by cauchywei on 2017/8/17.
//

#ifndef DCRAFT_SHIBANATIVE_H
#define DCRAFT_SHIBANATIVE_H


#include <string>
#include "../gui/window/INativeWindow.h"
#include "../common/ShibaTypes.h"
#include "../utils/Interface.h"

namespace shiba {
    namespace platform {

        using namespace shiba::window;

        class INativeService : public Interface {

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

        class INativeWindow : public Interface {
        public:
            virtual bool isOpen() = 0;

            virtual void close() = 0;

            virtual int getWidth() = 0;

            virtual int getHeight() = 0;

            virtual void show() = 0;

            virtual bool addListener(INativeWindowListener *listener) = 0;

            virtual bool removeListener(INativeWindowListener *listener) = 0;

            virtual void attachGL() = 0;

            virtual void detachGL() = 0;

            virtual void swapSurface() = 0;
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

        enum LogLevel {
            error,
            warning,
            info,
            debug,
            verbose
        };

        class ILogService : public Interface {
        public:
            virtual void v(const std::string &tag, const std::string &msg) {
                log(LogLevel::verbose, tag, msg);
            }

            virtual void d(const std::string &tag, const std::string &msg) {
                log(LogLevel::debug, tag, msg);
            }

            virtual void i(const std::string &tag, const std::string &msg) {
                log(LogLevel::info, tag, msg);
            }

            virtual void w(const std::string &tag, const std::string &msg) {
                log(LogLevel::warning, tag, msg);
            }

            virtual void e(const std::string &tag, const std::string &msg) {
                log(LogLevel::error, tag, msg);
            }

            virtual void log(LogLevel level, const std::string &tag, const std::string &msg) {
                switch (level) {
                    case error:
                        printf("[e]");
                        break;
                    case warning:
                        printf("[w]");
                        break;
                    case info:
                        printf("[i]");
                        break;
                    case debug:
                        printf("[d]");
                        break;
                    case verbose:
                        printf("[v]");
                        break;
                    default:
                        printf("");
                }
                printf("%s: %s\n", tag.c_str(), msg.c_str());
            }
        };


        class INativeController : public Interface {
        public:
            virtual INativeWindowService *getWindowService() = 0;

            virtual INativeEventService *getEventService() = 0;

            virtual ILogService *getLogService() = 0;
        };

    }
}


#endif //DCRAFT_SHIBANATIVE_H
