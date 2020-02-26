#pragma once
#include "Scene.h"

namespace window {
    void InitWindow(char *programName);
    void MainLoop();
    Scene& GetScene();
}
