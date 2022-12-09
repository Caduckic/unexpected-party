#ifndef _CAMERA_MANAGER_HPP_
#define _CAMERA_MANAGER_HPP_

#include "raylib.h"
//#include "config.hpp"

class CameraManager {
private:
    Camera2D cam;
    static CameraManager instance;
    CameraManager() = default;
public:
    static CameraManager& Get() {
        return instance;
    }

    void LoadCam() {
        cam = {{0,0}, {0,0}, 0, GetScreenHeight() / 256.f};
    }

    Camera2D& GetCam() {
        return cam;
    }

    ~CameraManager() = default;
    CameraManager(const CameraManager&) = delete;
};

CameraManager CameraManager::instance;

#endif