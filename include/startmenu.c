#include "updatepos.c"

void StartMenu(Camera2D camera){
  Vector2 clickCord = {0,0};
  float menuWidth = MeasureText("MENU", 48);
  float startWidth = MeasureText("START", 48);
  float optionsWidth = MeasureText("OPTIONS", 48);
  float quitWidth = MeasureText("QUIT", 48);

  Rectangle button = {
    .x = WIDTH/2.0 - menuWidth/2.0,
    .y = HEIGHT/14,
    .width = (menuWidth + 2.0),
    .height = HEIGHT/18
  };

  Rectangle button2 = {
    .x = WIDTH/2 - startWidth/2,
    .y = (button.y + button.height * 1.5),
    .width = startWidth + 3,
    .height = button.height
  };

  Rectangle button3 = {
    .x = WIDTH/2 - optionsWidth/2,
    .y = (button2.y + button2.height * 1.5),
    .width = optionsWidth + 2,
    .height = button2.height
  };

  Rectangle button4 = {
    .x = WIDTH/2 - quitWidth/2,
    .y = (button3.y + button2.height * 1.5),
    .width = quitWidth + 3,
    .height = button2.height
  };

  while(!WindowShouldClose()){
  BeginDrawing();
  BeginMode2D(camera);
  ClearBackground(BLACK);
    clickCord = GetMousePosition();
    DrawRectangle(button.x, button.y, button.width, button.height, RAYWHITE);
    DrawText("MENU", button.x + 1, button.y, 48, BLACK);
    DrawRectangle(button2.x, button2.y, button2.width, button2.height, RAYWHITE);
    DrawText("START", button2.x + 1, button2.y, 48, BLACK);
    DrawRectangle(button3.x, button3.y, button3.width, button3.height, RAYWHITE);
    DrawText("OPTIONS", button3.x + 1, button3.y, 48, BLACK);
    DrawRectangle(button4.x, button4.y, button4.width, button4.height, RAYWHITE);
    DrawText("QUIT", button4.x + 1, button4.y, 48, BLACK);
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
      if(CheckCollisionPointRec(clickCord, button2))
        break;
      //if(CheckCollisionpointRec(clickCord, button3))
      if(CheckCollisionPointRec(clickCord, button4)){
        CloseWindow();
        break;
      }
    }
  EndMode2D();
  EndDrawing();
  }
};