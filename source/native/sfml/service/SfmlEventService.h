//
// Created by cauchywei on 2017/8/19.
//

#ifndef SHIBA_SFMLEVENTSERVICE_H
#define SHIBA_SFMLEVENTSERVICE_H

#include "../../ShibaNative.h"
#include "../../../utils/List.h"

namespace shiba {
    namespace native {
        namespace sfml {


            class SfmlEventService : public INativeEventService {

            public:
                bool addListener(INativeEventListener *listener) override;

                bool removeListener(INativeEventListener *listener) override;

                ~SfmlEventService() override;

            private:
                List<INativeEventListener *> listeners;
            };

        }
    }
}
#endif //SHIBA_SFMLEVENTSERVICE_H
