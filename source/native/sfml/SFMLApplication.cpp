//
// Created by cauchywei on 2017/8/17.
//

#include "../../Application.h"
#include "SFMLApplication.h"
#include "SFMLController.h"
#include "../../SFMLMain.h"

using namespace shiba;

namespace shiba {
    namespace native {
        namespace sfml {


        }
    }
}

using namespace shiba::native::sfml;

int SFMLApplicationMain() {
    auto controller = createSFMLController();
    setAppController(controller);
    GLRendererMain();
    destroySFMLController(controller);
}

int setupSFMLRenderer() {
    SFMLApplicationMain();
}