#ifndef _MASK_TEXTURE_HPP_
#define _MASK_TEXTURE_HPP_

#include "raylib.h"
#include "config.hpp"

Vector2 ConvertToScreen(Vector2& positon);

class MaskTexture {
private:
    RenderTexture2D texture;
    static MaskTexture instance;
    MaskTexture() = default;
public:
    ~MaskTexture() = default;
    MaskTexture(const MaskTexture&) = delete;

    void LoadTexture() {
        texture = LoadRenderTexture(SCREEN_SIZE.x, SCREEN_SIZE.y);
    }

    void UnloadTexture() {
        UnloadRenderTexture(texture);
    }

    static MaskTexture& Get() {
        return instance;
    }
    
    RenderTexture2D& GetTexture() {
        return texture;
    }

    void ClearTexture() {
        BeginTextureMode(texture);
        ClearBackground({0,0,0,0});
        EndTextureMode();
    }

    void MaskAroundPlayers(Vector2 p1Pos, Vector2 p2Pos) {
        BeginTextureMode(texture);

        // clears render texture
        ClearBackground({0,0,0,0});

        // checks every pixel and draws black if it doesn't collide with mouse position with cutOutRadius
        for (int i {0}; i < 256; i++) {
            for (int j {0}; j < 256; j++) {
                if (!CheckCollisionPointCircle({(float)j, (float)i}, ConvertToScreen(p1Pos), 32) && !CheckCollisionPointCircle({(float)j, (float)i}, ConvertToScreen(p2Pos), 32)) {
                    DrawPixel(j, i, _COLOR4);
                }
            }
        }
        EndTextureMode();
    }

    void MaskAroundPlayer(Vector2 point) {
        BeginTextureMode(texture);

        // clears render texture
        ClearBackground({0,0,0,0});

        // checks every pixel and draws black if it doesn't collide with mouse position with cutOutRadius
        for (int i {0}; i < 256; i++) {
            for (int j {0}; j < 256; j++) {
                if (!CheckCollisionPointCircle({(float)j, (float)i}, ConvertToScreen(point), 32)) {
                    DrawPixel(j, i, _COLOR4);
                }
            }
        }
        EndTextureMode();
    }

    void FillTexture() {
        BeginTextureMode(texture);

        ClearBackground(_COLOR4);

        EndTextureMode();
    }

    void DrawTexture() {
        DrawTextureRec(texture.texture, { 0, 0, (float)texture.texture.width, (float)-texture.texture.height }, { 0, 0 }, WHITE);
        //DrawTexturePro(texture.texture, { 0, 0, (float)texture.texture.width, (float)-texture.texture.height }, {0,0,(float)GetScreenWidth(),(float)GetScreenHeight()}, { 0, 0 }, 0, WHITE);
    }
};

MaskTexture MaskTexture::instance;

// converts faster than GetScreenToWorld, you need to know exact screen scaling tho so not universal
Vector2 ConvertToScreen(Vector2& positon) {
    // using ints so the circle stays clean and consistant
    int x = positon.x;
    int y = positon.y;
    return {(float)x, (float)y};
}

#endif