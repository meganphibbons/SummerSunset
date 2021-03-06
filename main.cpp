// Created by Megan Phibbons

#include <allegro.h>
#include <iostream>
#include <vector>

using namespace std;

void init();
void deinit();

int main()
{
    init();

    // The number of fireflies to be created
    const int NUM_FIREFLIES = 75;

    // map of the scene that blips
    BITMAP* nightScene = create_bitmap(SCREEN_W, SCREEN_H);

    // Random positions and colors for grass texture. Needs to stay constant to avoid grass changing positions
    vector<int> grassX;
    vector<int> grassY;
    vector<int> grassColor;
    for(int i = 0; i < 1000; i++)
    {
        int g = rand() % 30 + 100;
        int x = rand() % SCREEN_W;
        int y = rand() % (SCREEN_H) + (SCREEN_H - 100);
        grassX.push_back(x);
        grassY.push_back(y);
        grassColor.push_back(g);
    }

    // Main loop of code
    while(!key[KEY_ESC])
    {
        // creates nighttime background
        rectfill(nightScene, 0, 0, SCREEN_W, SCREEN_H, makecol(72, 61, 139));

        // Process of creating the sunset background
        int r = 72, g = 61, b = 139;
        int radius = 0;
        for(int rad = SCREEN_W / 2; rad >= 0; rad--)
        {
            circlefill(nightScene, SCREEN_W / 2, SCREEN_H - 100, rad, makecol(r, g, b));
            g--;
            b++;
            radius = rad;
            if(g == 0)
                break;
        }
        for(int rad = radius; rad >= 0; rad--)
        {
            circlefill(nightScene, SCREEN_W / 2, SCREEN_H - 100, rad, makecol(r, g, b));
            r++;
            b--;
            radius = rad;
            if(b == 0)
                break;
        }
        circlefill(nightScene, SCREEN_W / 2, SCREEN_H - 100, radius + 25, makecol(255,70,0));

        // Grass
        rectfill(nightScene, 0, SCREEN_H - 100, SCREEN_W, SCREEN_H, makecol(10, 100, 0));

        // Placing the grass texture
        for(int i = 0; i < 1000; i++)
        {
            triangle(nightScene, grassX[i], grassY[i], grassX[i] + 5, grassY[i] + 5, grassX[i] - 5, grassY[i] + 5, makecol(10, grassColor[i], 0));
        }

        // Creating the tree branch
        int branchOutline[8] = {SCREEN_W - 123, SCREEN_H - 223, SCREEN_W - 123, SCREEN_H - 230, SCREEN_W - 182, SCREEN_H - 232, SCREEN_W - 184, SCREEN_H - 228};
        int branchFill[8] = {SCREEN_W - 124, SCREEN_H - 224, SCREEN_W - 124, SCREEN_H - 229, SCREEN_W - 181, SCREEN_H - 231, SCREEN_W - 183, SCREEN_H - 229};
        polygon(nightScene, 4, branchOutline, makecol(51, 25, 0));
        polygon(nightScene, 4, branchFill, makecol(102, 51, 0));

        // Creating the tree. Circles are the tree leaves
        rectfill(nightScene, SCREEN_W - 125, SCREEN_H - 75, SCREEN_W - 75, SCREEN_H - 275, makecol(102, 51, 0));
        ellipsefill(nightScene, SCREEN_W - 100, SCREEN_H - 125, 10, 17, makecol(51, 25, 0));
        circlefill(nightScene, SCREEN_W - 125, SCREEN_H - 275, 15, makecol(51, 102, 0));
        circlefill(nightScene, SCREEN_W - 115, SCREEN_H - 265, 15, makecol(51, 102, 0));
        circlefill(nightScene, SCREEN_W - 105, SCREEN_H - 260, 15, makecol(51, 102, 0));
        circlefill(nightScene, SCREEN_W - 95, SCREEN_H - 265, 15, makecol(51, 102, 0));
        circlefill(nightScene, SCREEN_W - 85, SCREEN_H - 270, 15, makecol(51, 102, 0));
        circlefill(nightScene, SCREEN_W - 115, SCREEN_H - 285, 15, makecol(51, 102, 0));
        circlefill(nightScene, SCREEN_W - 105, SCREEN_H - 295, 15, makecol(51, 102, 0));
        circlefill(nightScene, SCREEN_W - 95, SCREEN_H - 285, 15, makecol(51, 102, 0));
        circlefill(nightScene, SCREEN_W - 85, SCREEN_H - 285, 15, makecol(51, 102, 0));
        circlefill(nightScene, SCREEN_W - 130, SCREEN_H - 260, 15, makecol(51, 102, 0));
        circlefill(nightScene, SCREEN_W - 75, SCREEN_H - 260, 15, makecol(51, 102, 0));
        circlefill(nightScene, SCREEN_W - 75, SCREEN_H - 270, 15, makecol(51, 102, 0));

        // Creating the fireflies
        vector<int> fireflyX;
        vector<int> fireflyY;
        for(int i = 0; i < NUM_FIREFLIES; i++)
        {
            int x = rand() % SCREEN_W;
            int y = rand() % SCREEN_H - 150;
            fireflyX.push_back(x);
            fireflyY.push_back(y);
        }

        // Brightest firefly light followed by dimming fireflies then re-brightening fireflies to simulate them flashing
        for(int i = 0; i < NUM_FIREFLIES; i++)
        {
            circlefill(nightScene, fireflyX[i], fireflyY[i], 1, makecol(255,255,0));
        }
        blit(nightScene, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(200);

        for(int i = 0; i < NUM_FIREFLIES; i++)
        {
            circlefill(nightScene, fireflyX[i], fireflyY[i], 1, makecol(255,215,0));
        }
        blit(nightScene, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(200);

        for(int i = 0; i < NUM_FIREFLIES; i++)
        {
            circlefill(nightScene, fireflyX[i], fireflyY[i], 1, makecol(218,165,32));
        }
        blit(nightScene, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(200);

        for(int i = 0; i < NUM_FIREFLIES; i++)
        {
            circlefill(nightScene, fireflyX[i], fireflyY[i], 1, makecol(0, 0, 0));
        }
        blit(nightScene, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(400);

        for(int i = 0; i < NUM_FIREFLIES; i++)
        {
            circlefill(nightScene, fireflyX[i], fireflyY[i], 1, makecol(218,165,32));
        }
        blit(nightScene, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(200);

        for(int i = 0; i < NUM_FIREFLIES; i++)
        {
            circlefill(nightScene, fireflyX[i], fireflyY[i], 1, makecol(255,215,0));
        }
        blit(nightScene, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(200);

        for(int i = 0; i < NUM_FIREFLIES; i++)
        {
            circlefill(nightScene, fireflyX[i], fireflyY[i], 1, makecol(255,255,0));
        }
        blit(nightScene, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(200);
    }
    deinit();
    return 0;
}
END_OF_MAIN()

void init()
{
    int depth, res;
    allegro_init();
    depth = desktop_color_depth();
    if(depth == 0)
        depth = 32;
    set_color_depth(depth);
    res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
    if(res != 0)
    {
        allegro_message(allegro_error);
        exit(-1);
    }
    install_timer();
    install_keyboard();
    install_mouse();
}

void deinit()
{
    clear_keybuf();
}
