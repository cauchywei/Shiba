//
// Created by cauchywei on 2017/8/20.
//

#ifndef SHIBA_MODEL_H
#define SHIBA_MODEL_H


#include <string>
#include "Mesh.h"

namespace shiba {
    namespace framework {
        namespace model {
            class Model: public Mesh {
            public:
                Model(const std::string &name);

            protected:
                std::string name;
            };
        }
    }
}



#endif //SHIBA_MODEL_H
