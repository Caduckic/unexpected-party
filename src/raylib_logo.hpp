#ifndef _RAYLIB_LOGO_HPP_
#define _RAYLIB_LOGO_HPP_

#include <cmath>
#include "raylib.h"
#include "config.hpp"

bool IsColorEqual(const Color& col1, const Color& col2);

class RaylibLogo {
private:
    int state;
    float timeCounter;
    float modRemainder;
    bool blink;
    int letterCount;
    Color color;
    Rectangle topLeftPoint;
    Rectangle topRect;
    Rectangle leftRect;
    Rectangle rightRect;
    Rectangle bottomRect;
    bool finished;
public:
    RaylibLogo() : state{0}, timeCounter{0}, modRemainder{0}, blink{true}, letterCount{0}, color{_COLOR4}, topLeftPoint{0,0,16,16}, topRect{16,0,0,16}, leftRect{0,16,16,0}, rightRect{240,16,16,0}, bottomRect{16,240,0,16}, finished{false} {};
    ~RaylibLogo() = default;

    bool IsFinished() {
        return finished;
    }

    void update() {
        if (IsWindowFocused()) timeCounter += GetFrameTime();
        if (state == 0) {
            float previousRemainder = modRemainder;
            modRemainder = std::fmod(timeCounter * 100.f, 25.f);
            if (previousRemainder > modRemainder) blink = !blink;
            if (timeCounter >= 2) {
                timeCounter = 2;
                modRemainder = 0;
                blink = false;
                state = 1;
            }
        }
        else if (state == 1) {
            topRect.width = 180.f * (timeCounter - 2.f);
            leftRect.height = 180.f * (timeCounter - 2.f);
            if (timeCounter >= 3.5f || 180.f * (timeCounter - 2.f) >= 240) {
                timeCounter = 3.5f;
                topRect.width = 240;
                leftRect.height = 240;
                state = 2;
            }
        }
        else if (state == 2) {
            rightRect.height = 180.f * (timeCounter - 3.5f);
            bottomRect.width = 180.f * (timeCounter - 3.5f);
            if (timeCounter >= 5) {
                timeCounter = 5;
                rightRect.height = 240;
                bottomRect.width = 240;
                state = 3;
            }
        }
        else if (state == 3) {
            float previousRemainder = modRemainder;
            modRemainder = std::fmod(timeCounter * 100.f, 20.f);
            if (previousRemainder > modRemainder) letterCount++;
            if (timeCounter >= 7) {
                timeCounter = 7;
                modRemainder = 0;
                state = 4;
            }
        }
        else if (state == 4) {
            float previousRemainder = modRemainder;
            modRemainder = std::fmod(timeCounter * 100.f, 27.777f);
            if (previousRemainder > modRemainder) {
                if (IsColorEqual(color, _COLOR4)) {
                    color = _COLOR3;
                }
                else if (IsColorEqual(color, _COLOR3)) {
                    color = _COLOR2;
                }
                else if (IsColorEqual(color, _COLOR2)) {
                    color = _COLOR1;
                }
            }
            if (timeCounter >= 8) {
                finished = true;
            }
        }
    }

    void render() {
        if (!blink) DrawRectangleRec(topLeftPoint, color);
        DrawRectangleRec(topRect, color);
        DrawRectangleRec(leftRect, color);
        DrawRectangleRec(rightRect, color);
        DrawRectangleRec(bottomRect, color);
        DrawText(TextSubtext("raylib", 0, letterCount), 256/2 - 44, 256/2 + 48, 50, color);
    }
};

bool IsColorEqual(const Color& col1, const Color& col2) {
    return (col1.a == col2.a && col1.b == col2.b && col1.g == col2.g && col1.r == col2.r);
}

#endif