//
// Created by cauchywei on 2017/8/19.
//

#include "SfmlEventService.h"

namespace shiba {
    namespace platform {
        namespace sfml {

            bool SfmlEventService::addListener(INativeEventListener *listener) {
                if (listeners.contains(listener)) {
                    return false;
                } else {
                    listeners.add(listener);
                    return true;
                }
            }

            bool SfmlEventService::removeListener(INativeEventListener *listener) {
                return listeners.remove(listener);
            }

            SfmlEventService::~SfmlEventService() {

            }
        }
    }
}