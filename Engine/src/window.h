#pragma once
#include "Scene.h"

using namespace engine;

namespace window {
    void InitWindow(char *programName);
    void MainLoop();
    Scene& GetScene();
}
