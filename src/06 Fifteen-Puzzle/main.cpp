#include <raylib.h>

#include <utility.hpp>

#include <iostream>

int main()
{
    InitWindow(256, 256, "15-Puzzle!");
    SetTargetFPS(60);

    Texture t { LoadTexture("images/15.png") };

    int w = 64;
    int grid[6][6] = { };
    Sprite sprite[20];

    int n=0;
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
        {
            n++;
            sprite[n].set_texture(t);
            sprite[n].set_texture_rec({i * w * 1.0f, j * w * 1.0f, w * 1.0f, w * 1.0f});
            grid[i+1][j+1]=n;
        }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            auto pos = GetMousePosition();
            int x = pos.x/w + 1;
            int y = pos.y/w + 1;

            int dx=0;
            int dy=0;

            if (grid[x+1][y]==16) {dx=1; dy=0;};
            if (grid[x][y+1]==16) {dx=0; dy=1;};
            if (grid[x][y-1]==16) {dx=0; dy=-1;};
            if (grid[x-1][y]==16) {dx=-1;dy=0;};

            int n = grid[x][y];
            grid[x][y] = 16;
            grid[x+dx][y+dy] = n;

            //animation
            sprite[16].move(-dx*w,-dy*w);
            float speed=3;

            for (int i=0;i<w;i+=speed)
            {
                sprite[n].move(speed*dx,speed*dy);
                draw(sprite[16]);
                draw(sprite[n]);
            }
        }

        ClearBackground(RAYWHITE);
        for (int i=0;i<4;i++)
            for (int j=0;j<4;j++)
            {
                int n = grid[i+1][j+1];
                sprite[n].set_position(i*w,j*w);
                draw(sprite[n]);
            }
        EndDrawing();
    }

    UnloadTexture(t);
    CloseWindow();
    return 0;
}
