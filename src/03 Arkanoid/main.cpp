#include <raylib.h>

#include <cstdlib>
#include <ctime>

#include <utility.hpp>

int main()
{
    std::srand(time(0));

    InitWindow(520, 450, "Arkanoid!");
    SetTargetFPS(60);

    const auto t1 { LoadTexture("images/block01.png")    };
    const auto t2 { LoadTexture("images/background.jpg") };
    const auto t3 { LoadTexture("images/ball.png")       };
    const auto t4 { LoadTexture("images/paddle.png")     };

    Sprite sBackground(t2), sBall(t3), sPaddle(t4);
    sPaddle.set_position(300, 440);

    Sprite block[1000];

    int n=0;
    for (int i=1;i<=10;i++)
        for (int j=1;j<=10;j++)
        {
            block[n].set_texture(t1);
            block[n].set_position(i * 43, j * 20);
            n++;
        }

    float dx = 6, dy = 5;
    float x = 300, y = 300;

    while (!WindowShouldClose())
    {
        x += dx;
        for (int i=0;i<n;i++)
            if (CheckCollisionRecs({x + 3, y + 3, 6, 6}, block[i].get_bounds())) 
            {
                block[i].set_position(-100,0);
                dx = -dx;
            }

        y += dy;
        for (int i=0;i<n;i++)
            if (CheckCollisionRecs({x + 3, y + 3, 6, 6}, block[i].get_bounds())) 
            {
                block[i].set_position(-100,0);
                dy = -dy;
            }

        if (x<0 || x>520)  dx=-dx;
        if (y<0 || y>450)  dy=-dy;

        if (IsKeyDown(KEY_RIGHT))  sPaddle.move(6, 0);
        if (IsKeyDown(KEY_LEFT)) sPaddle.move(-6, 0);

        if (CheckCollisionRecs({x, y, 12, 12}, sPaddle.get_bounds()))
            dy = -(rand() % 5 + 2);

        sBall.set_position(x,y);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        draw(sBackground);
        draw(sBall);
        draw(sPaddle);

        for (int i=0;i<n;i++)
            draw(block[i]);

        EndDrawing();
    }

    UnloadTexture(t1);
    UnloadTexture(t2);
    UnloadTexture(t3);
    UnloadTexture(t4);
    CloseWindow();
    return 0;
}
