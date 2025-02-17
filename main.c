#include <stdio.h>
#include "include/startmenu.c"

Rectangle rec = {
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
    .center = {WIDTH/2, HEIGHT/2},
    .vert1 = {player.center.x, player.center.y + 10},
    .vert2 = {player.vert1.x - 10, player.vert1.y + 10},
    .vert3 = {player.vert1.x + 10, player.vert1.y + 10}
  };

  Matrix rotate = {
    .m0 = cos(player.angle),
    .m4 = -sin(player.angle),
    .m1 = sin(player.angle),
    .m5 = cos(player.angle)
  };

  SetTargetFPS(60);
  GetFontDefault();
  InitWindow(WIDTH, HEIGHT, "Window");
  StartMenu(camera);

  /////////////
  //MAIN LOOP//
  /////////////
  while(!WindowShouldClose()){
    BeginDrawing();
    BeginMode2D(camera);
    ClearBackground(BLACK);
    UpdatePosition(&player, rotate);
    EndMode2D();
    EndDrawing();
  }
  CloseWindow();
  return 0;
} 