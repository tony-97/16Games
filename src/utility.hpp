#pragma once

#include <raylib.h>

class Sprite
{
public:
    constexpr explicit Sprite() {  }
    constexpr explicit Sprite(const Texture2D& t, float x = 0.0f, float y = 0.0f)
        : mTexture { t }, mX { x }, mY { y },
          mCrop { 0.0f, 0.0f, static_cast<float>(t.width), static_cast<float>(t.height) }
    {

    }

    constexpr void set_position(float x, float y)
    {
        mX = x; mY = y;
    }

    constexpr void move(float dx, float dy)
    {
        mX += dx; mY += dy;
    }

    constexpr void set_texture(const Texture2D& t)
    {
        mTexture = t;
    }

    constexpr void set_texture_rec(Rectangle r)
    {
        mCrop = r;
    }

    constexpr Rectangle get_bounds() const
    {
        return { mX,
                 mY,
                 static_cast<float>(mTexture.width),
                 static_cast<float>(mTexture.height) };
    }
private:
    Texture2D mTexture {  };
    float mX {  };
    float mY {  };
    Rectangle mCrop {  };
    friend void draw(const Sprite&);
};

inline void draw(const Sprite& sp)
{
    DrawTextureRec(sp.mTexture, sp.mCrop, { sp.mX, sp.mY }, RAYWHITE);
}
