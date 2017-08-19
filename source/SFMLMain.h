//
// Created by cauchywei on 2017/8/17.
//

#ifndef DCRAFT_DCRAFTMAIN_H
#define DCRAFT_DCRAFTMAIN_H

extern int setupSFMLRenderer();

namespace shiba {
    namespace native {
        namespace sfml {
            extern int _sfml_main(int argc, char **argv);
        }
    }
}


#endif //DCRAFT_DCRAFTMAIN_H
