//
// Created by cauchywei on 2017/8/17.
//

#ifndef DCRAFT_OSXSFMLCONTROLLER_H
#define DCRAFT_OSXSFMLCONTROLLER_H


#include "../../gui/window/INativeWindow.h"
#include "../ShibaNative.h"


namespace shiba {
    namespace platform {
        namespace sfml {
            using namespace shiba::platform;

            class ISFMLWindow: virtual Interface {

            };

            extern INativeController *createSFMLController();

            extern void destroySFMLController(INativeController *controller);

        }
    }
}


#endif //DCRAFT_OSXSFMLCONTROLLER_H
