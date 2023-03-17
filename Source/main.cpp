#include "raylib.h"
#include <string>

struct animData
{
    Rectangle rectangle;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{

    // window dimension
    const int windowWidth{800};
    const int windowHeight{500};

    // initialize window
    InitWindow(windowWidth, windowHeight, "Line's Runner");

    const int gravity{1'200};

    // scarfy veriables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    animData scarfyData;
    scarfyData.rectangle.width = scarfy.width / 6;
    scarfyData.rectangle.height = scarfy.height;
    scarfyData.rectangle.x = 0.0;
    scarfyData.rectangle.y = 0.0;
    scarfyData.pos.x = windowWidth / 2 - scarfyData.rectangle.width / 2;
    scarfyData.pos.y = windowHeight - scarfyData.rectangle.height;
    // animation frame
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    int velocity{0};

    const int jumpVelocity{-600};

    bool isInAir = false;

    // nebula veriables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    animData nebulaData;
    nebulaData.rectangle = {0.0, 0.0, nebula.width / float(8), nebula.height / float(8)};
    nebulaData.pos = {windowWidth, windowHeight - nebulaData.rectangle.height};
    // nebula animation veriables
    nebulaData.frame = 0;
    nebulaData.updateTime = 1.0 / 12.0;
    nebulaData.runningTime = 0.0;
    float nebulaPad{20.0};
    // nebula x velocity
    int nebulaVelocity{-400};

    Texture2D backgroundFar = LoadTexture("textures/far-buildings.png");
    Texture2D backgroundMid = LoadTexture("textures/back-buildings.png");
    Texture2D backgroundFore = LoadTexture("textures/foreground.png");
    float bgX{};
    float bgY{};
    float bgZ{};

    float score{0.0f};
    float tmpScore{score};
    bool collision{};
    bool check{};
    std::string scoreText = "Score: ";
    float highScore{0.0f};
    std::string highScoreText = "High Score: ";

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // delta time
        float dT{GetFrameTime()};

        BeginDrawing();
        ClearBackground(BLACK);

        bgX -= 20 * dT;
        bgY -= 40 * dT;
        bgZ -= 80 * dT;

        // draw the background
        Vector2 bgfar1Pos{bgX, 0.0};
        DrawTextureEx(backgroundFar, bgfar1Pos, 0.0, 2.5, WHITE);
        Vector2 bgfar2Pos{bgX + float(backgroundFar.width) * 2.5f, 0.0};
        DrawTextureEx(backgroundFar, bgfar2Pos, 0.0, 2.5, WHITE);
        Vector2 bgfar3Pos{bgX + float(backgroundFar.width) * 2.5f * 2.0f, 0.0};
        DrawTextureEx(backgroundFar, bgfar3Pos, 0.0, 2.5, WHITE);

        Vector2 bgmid1Pos{bgY, float(windowHeight) - float(backgroundFore.height) * 2.25f};
        DrawTextureEx(backgroundMid, bgmid1Pos, 0.0, 2.0, WHITE);
        Vector2 bgmid2Pos{bgY + float(backgroundMid.width) * 2.0f, float(windowHeight) - float(backgroundFore.height) * 2.25f};
        DrawTextureEx(backgroundMid, bgmid2Pos, 0.0, 2.0, WHITE);
        Vector2 bgmid3Pos{bgY + float(backgroundMid.width) * 2.0f * 2.0f, float(windowHeight) - float(backgroundFore.height) * 2.25f};
        DrawTextureEx(backgroundMid, bgmid3Pos, 0.0, 2.0, WHITE);

        Vector2 bgfore1Pos{bgZ, float(windowHeight) - float(backgroundFore.height) * 1.5f};
        DrawTextureEx(backgroundFore, bgfore1Pos, 0.0, 1.5, WHITE);
        Vector2 bgfore2Pos{bgZ + float(backgroundFore.width) * 1.5f, float(windowHeight) - float(backgroundFore.height) * 1.5f};
        DrawTextureEx(backgroundFore, bgfore2Pos, 0.0, 1.5, WHITE);
        Vector2 bgfore3Pos{bgZ + float(backgroundFore.width) * 1.5f * 2.0f, float(windowHeight) - float(backgroundFore.height) * 1.5f};
        DrawTextureEx(backgroundFore, bgfore3Pos, 0.0, 1.5, WHITE);

        if (bgX <= -backgroundFar.width * 2.5)
        {
            bgX = 0.0;
        }
        if (bgY <= -backgroundMid.width * 2.0)
        {
            bgY = 0.0;
        }
        if (bgZ <= -backgroundFore.width * 1.5)
        {
            bgZ = 0.0;
        }

        if (scarfyData.pos.y >= windowHeight - scarfyData.rectangle.height)
        {
            // is on the ground
            isInAir = false;

            velocity = 0;
        }
        else
        {
            // is in the air
            isInAir = true;

            // apply gravity
            velocity += gravity * dT;
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity;
        }

        // update nebula position
        nebulaData.pos.x += nebulaVelocity * dT;

        // update scarfy position
        scarfyData.pos.y += velocity * dT;

        scarfyData.runningTime += dT;

        if (scarfyData.runningTime >= scarfyData.updateTime && !isInAir)
        {
            scarfyData.runningTime = 0.0;

            // update animation frame
            scarfyData.rectangle.x = scarfyData.frame * scarfyData.rectangle.width;
            scarfyData.frame++;
            if (scarfyData.frame > 5)
            {
                scarfyData.frame = 0;
            }

            // same function as above
            // scarfyRec.x += (scarfy.width / 6);
        }

        nebulaData.runningTime += dT;
        if (nebulaData.runningTime >= nebulaData.updateTime)
        {
            nebulaData.runningTime = 0.0;

            nebulaData.rectangle.x = nebulaData.frame * nebulaData.rectangle.width;
            nebulaData.frame++;
            if (nebulaData.frame > 7)
            {
                nebulaData.frame = 0.0;
            }

            if (nebulaData.pos.x + nebulaData.rectangle.width < 0)
            {
                score += 5.0f;
                nebulaData.pos.x = windowWidth;
            }
        }

        Rectangle nebulaRec{
            nebulaData.pos.x + nebulaPad,
            nebulaData.pos.y + nebulaPad,
            nebulaData.rectangle.width - 2 * nebulaPad,
            nebulaData.rectangle.height - 2 * nebulaPad};

        Rectangle scarfyRec{
            scarfyData.pos.x,
            scarfyData.pos.y,
            scarfyData.rectangle.width,
            scarfyData.rectangle.height};

        if (CheckCollisionRecs(nebulaRec, scarfyRec))
        {
            collision = true;
        }

        if (collision)
        {
            if (highScore < score && !check)
            {
                highScore = score;
                highScoreText.clear();
                highScoreText.append("High Score: ");
                highScoreText.append(std::to_string(highScore), 0, 5);
                check = true;
            }

            score = 0.0f;

            DrawText("Game Over", windowWidth * 3 / 7, windowHeight / 2, 35, WHITE);
            DrawText("Press q for Try Again", windowWidth * 3 / 8, windowHeight / 2 + 40, 25, WHITE);
            if (IsKeyPressed(KEY_Q))
            {
                collision = false;
                check = false;
                nebulaData.pos.x = windowWidth + 70;
            }
        }
        else
        {
            // draw nebula
            DrawTextureRec(nebula, nebulaData.rectangle, nebulaData.pos, WHITE);

            // draw scarfy
            DrawTextureRec(scarfy, scarfyData.rectangle, scarfyData.pos, WHITE);

            // draw score
            if (score != tmpScore)
            {
                tmpScore = score;
                scoreText.clear();
                scoreText.append("Score: ");
                scoreText.append(std::to_string(tmpScore), 0, 5);
            }

            DrawText(scoreText.c_str(), windowWidth - 200, 50, 20, WHITE);
            DrawText(highScoreText.c_str(), 50, 50, 20, WHITE);
        }

        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(backgroundFar);
    UnloadTexture(backgroundMid);
    UnloadTexture(backgroundFore);

    CloseWindow();

    return 0;
}