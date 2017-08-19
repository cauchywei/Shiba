//
// Created by cauchywei on 2017/8/17.
//

#include "launcher.h"
#include "gui/window/GuiWindow.h"
#include "framework/GLWindow.h"
#include "Application.h"

using namespace shiba::launcher;
using namespace shiba;

void GameGUIMain() {
//    Launcher launcherWindow;
    shiba::framework::GLWindow launcherWindow;
    getApplication()->run(&launcherWindow);
}
