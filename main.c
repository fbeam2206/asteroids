#include <stdio.h>
#include "include/startmenu.c"
#include "raylib.h"

Rectangle laserBeam = {
  .x = 0,
  .y = 799,
  .width = 1600,
  .height = 2
};

int main(){

  Camera2D camera = {
    .zoom = 1,
    .offset = zero,
    .target = zero,
    .rotation = 0
  };

  ship player = {
    .angle = 0.05,
    .center = {WIDTH/2.0, HEIGHT/2.0},
    .vert1 = {player.center.x, player.center.y + 20},
    .vert2 = {player.vert1.x - 20, player.vert1.y + 25},
    .vert3 = {player.vert1.x + 20, player.vert1.y + 25}
  };

  SetTargetFPS(60);
  GetFontDefault();
  InitWindow(WIDTH, HEIGHT, "Window");
  StartMenu(camera);

  Image image= LoadImage("assets/ast2.jpg");
  Texture2D texture = LoadTextureFromImage(image);
  UnloadImage(image);

/*////////////////////////////////////
///////////// MAIN LOOP //////////////
///////////////////////////////////*/

  while(!WindowShouldClose()){
    BeginDrawing();
    BeginMode2D(camera);
    ClearBackground(BLACK);
    UpdatePosition(&player, &texture);
    EndMode2D();
    EndDrawing();
  }
  CloseWindow();
  return 0;
} 