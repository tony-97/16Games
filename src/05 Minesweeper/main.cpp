#include <raylib.h>

#include <cstdlib>
#include <ctime>

int main()
{
    std::srand(time(0));

    InitWindow(400, 400, "Minesweeper!");

    int w = 32;
    int grid[12][12];
    int sgrid[12][12]; //for showing

    Texture2D s { LoadTexture("images/tiles.png") };

    for (int i=1;i<=10;i++)
        for (int j=1;j<=10;j++)
        {
            sgrid[i][j]=10;
            if (rand()%5==0)  grid[i][j]=9;
            else grid[i][j]=0;
        }

    for (int i=1;i<=10;i++)
        for (int j=1;j<=10;j++)
        {
            int n=0;
            if (grid[i][j]==9) continue;
            if (grid[i+1][j]==9) n++;
            if (grid[i][j+1]==9) n++;
            if (grid[i-1][j]==9) n++;
            if (grid[i][j-1]==9) n++;
            if (grid[i+1][j+1]==9) n++;
            if (grid[i-1][j-1]==9) n++;
            if (grid[i-1][j+1]==9) n++;
            if (grid[i+1][j-1]==9) n++;
            grid[i][j]=n;
        }

    while (!WindowShouldClose())
    {
        const auto pos { GetMousePosition() };
        const int x = pos.x / w;
        const int y = pos.y / w;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))       sgrid[x][y] = grid[x][y];
        else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) sgrid[x][y] = 11;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i=1;i<=10;i++)
            for (int j=1;j<=10;j++)
            {
                if (sgrid[x][y] == 9) sgrid[i][j] = grid[i][j];
                Rectangle crop { sgrid[i][j] * w * 1.0f, 0.0f, w * 1.0f, w * 1.0f };
                Vector2 pos{ static_cast<float>(i * w), static_cast<float>(j * w) };
                DrawTextureRec(s, crop, pos, RAYWHITE);
            }
        EndDrawing();
    }

    UnloadTexture(s);
    CloseWindow();
    return 0;
}
