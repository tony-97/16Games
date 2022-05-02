#include <iterator>
#include <raylib.h>

#include <cstdlib>
#include <ctime>

#include <array>
#include <algorithm>

struct point
{
    int x {  };
    int y {  };
};

int main()
{
    std::srand(time(0));

    constexpr int screen_width  = 400;
    constexpr int screen_height = 533;
    InitWindow(screen_width, screen_height, "Doodle Game!");
    SetTargetFPS(60);

    Texture2D sBackground { LoadTexture("images/background.png") };
    Texture2D sPlat { LoadTexture("images/platform.png")   };
    Texture2D sPers { LoadTexture("images/doodle.png")     };

    std::array<point, 7> plat;

    std::transform(plat.begin(), plat.end(), plat.begin(),
            [](auto&&) -> point {
                return { std::rand() % screen_width, std::rand() % screen_height };
            });

    int x = 100;
    int y = 100;
    int h = 200;
    //float dx = 0.0f;
    float dy = 0.0f;

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT)) x += 3;
        if (IsKeyDown(KEY_LEFT))  x -= 3;

        dy += 0.2;
        y  += dy;
        if (y > 500) dy = -10;

        if (y < h)
            std::for_each(plat.begin(), plat.end(),
                    [&](auto&& p){
                        y = h;
                        p.y = p.y - dy;
                        if (p.y > screen_height) {
                            p.y = 0;
                            p.x = std::rand() % screen_width;
                        }
                    });

        std::for_each(plat.begin(), plat.end(), [&](const point& p) {
                    if ((x + 50 > p.x)
                     && (x + 20 < p.x + 68)
                     && (y + 70 > p.y)
                     && (y + 70 < p.y + 14)
                     && (dy>0))  dy = - 10;
                });

        BeginDrawing();
        DrawTexture(sBackground, 0, 0, RAYWHITE);
        DrawTexture(sPers, x, y, RAYWHITE);
        std::for_each(plat.begin(), plat.end(), [&](const point& p){
                    DrawTexture(sPlat, p.x, p.y, RAYWHITE);
                });
        EndDrawing();

    }

    return 0;
}
