#include "collision.c"
#include "raylib.h"
#include "sand.h"
#include <stdlib.h>
#include <time.h>

void UpdatePosition(ship* player, Texture* texture){

  if(currentState.spawnTime < currentState.spawnDelay){
    currentState.spawnTime += GetFrameTime();
  }
  if(currentState.shootTime < currentState.shootDelay){
    currentState.shootTime += GetFrameTime();
  }

  // TODO: ScoreCounter
  //       Collision

  if(IsKeyDown(KEY_W)){player->vert1.y -= 10;player->vert2.y -= 10;player->vert3.y -= 10;player->center.y -= 10;}
  if(IsKeyDown(KEY_S)){player->vert1.y += 10;player->vert2.y += 10;player->vert3.y += 10;player->center.y += 10;}
  if(IsKeyDown(KEY_A)){player->vert1.x -= 10;player->vert2.x -= 10;player->vert3.x -= 10;player->center.x -= 10;}
  if(IsKeyDown(KEY_D)){player->vert1.x += 10;player->vert2.x += 10;player->vert3.x += 10;player->center.x += 10;}

  // Rotation
  if(IsKeyDown(KEY_LEFT)){
    // Store original positions before modification
    float x1 = player->vert1.x - player->center.x;
    float y1 = player->vert1.y - player->center.y;
    float x2 = player->vert2.x - player->center.x;
    float y2 = player->vert2.y - player->center.y;
    float x3 = player->vert3.x - player->center.x;
    float y3 = player->vert3.y - player->center.y;

    // Compute sin and cos once for efficiency
    float cosA = cosf(player->angle);
    float sinA = sinf(player->angle);

    // Rotate and reassign
    player->vert1.x = player->center.x + x1 * cosA - y1 * sinA;
    player->vert1.y = player->center.y + x1 * sinA + y1 * cosA;

    player->vert2.x = player->center.x + x2 * cosA - y2 * sinA;
    player->vert2.y = player->center.y + x2 * sinA + y2 * cosA;

    player->vert3.x = player->center.x + x3 * cosA - y3 * sinA;
    player->vert3.y = player->center.y + x3 * sinA + y3 * cosA;
  }

  // Creating Laser
  if(IsKeyDown(KEY_SPACE) && currentState.shootTime >= currentState.shootDelay && currentState.laserCount < MAXCOUNT){
    Laser laser = {
      .pos = player->vert1,
      .dir = Vector2Normalize(Vector2Subtract(player->center, player->vert1)),
      .speed = 400.0,
      .vel = Vector2Scale(laser.dir, laser.speed),
      .hit = 0
    };
    currentState.laserArray[currentState.laserCount++] = laser;
    currentState.shootTime -= currentState.shootDelay;
  }

  // Creating Asteroid
  if(currentState.spawnTime >= currentState.spawnDelay && currentState.astCount < MAXCOUNT){
    srand(time(NULL));
    Asteroid ast = {
      .pos = Vector2Rotate((Vector2){1000,0}, rand()),
      .dir = Vector2Normalize(Vector2Subtract((Vector2){WIDTH/2, HEIGHT/2}, ast.pos)),
      .speed = rand()%150,
      .vel = Vector2Scale(ast.dir, ast.speed),
      .destroyed = 0
    };
    currentState.astArray[currentState.astCount++] = ast;
    currentState.spawnTime -= currentState.spawnDelay;
  }

  // Rotation
  if(IsKeyDown(KEY_RIGHT)){
    // Store original positions before modification
    float x1 = player->vert1.x - player->center.x;
    float y1 = player->vert1.y - player->center.y;
    float x2 = player->vert2.x - player->center.x;
    float y2 = player->vert2.y - player->center.y;
    float x3 = player->vert3.x - player->center.x;
    float y3 = player->vert3.y - player->center.y;

    // Compute sin and cos once for efficiency
    float cosA = cosf(-player->angle);
    float sinA = sinf(-player->angle);

    // Rotate and reassign
    player->vert1.x = player->center.x + x1 * cosA - y1 * sinA;
    player->vert1.y = player->center.y + x1 * sinA + y1 * cosA;

    player->vert2.x = player->center.x + x2 * cosA - y2 * sinA;
    player->vert2.y = player->center.y + x2 * sinA + y2 * cosA;

    player->vert3.x = player->center.x + x3 * cosA - y3 * sinA;
    player->vert3.y = player->center.y + x3 * sinA + y3 * cosA;
  }

  // Check for Collision
  Collision();

  // Draw Asteroids
  for(int astInd=0; astInd<=currentState.astCount; astInd++){
    Asteroid *ast = &currentState.astArray[astInd];
    ast->pos.x += ast->vel.x*GetFrameTime();
    ast->pos.y += ast->vel.y*GetFrameTime();
    if(ast->destroyed == 0){
      DrawCircleLines(ast->pos.x, ast->pos.y, 15,  WHITE);
    }
  }

  // Draw Lasers
  for(int laserInd=0; laserInd<currentState.laserCount; laserInd++){
    Laser *beam = &currentState.laserArray[laserInd];
    beam->pos.x += beam->vel.x*GetFrameTime();
    beam->pos.y += beam->vel.y*GetFrameTime();
    if(beam->hit == 0){
      DrawLine(beam->pos.x, beam->pos.y, beam->pos.x+beam->dir.x*10, beam->pos.y+beam->dir.y*10, WHITE);
    }
  }

  for(int scoreCounter = 0, ind = 0; ind <= currentState.astCount; ind++){
    Asteroid *ast = &currentState.astArray[ind];
    if(ast->destroyed == 1){scoreCounter++;}
    if(ind == currentState.astCount){currentState.score = scoreCounter;}
  }

  DrawRectangle(1200 - MeasureText("100", 42), 0, MeasureText("100", 48), 56, RAYWHITE);
  DrawText(TextFormat("%d", currentState.score-1), 1200-((float)MeasureText("100", 58)/2), 10, 48, BLACK);

  // Draw Player
  DrawLine(player->vert1.x, player->vert1.y, player->vert2.x, player->vert2.y, WHITE);
  DrawLine(player->vert2.x, player->vert2.y, player->center.x, player->center.y, WHITE);
  DrawLine(player->center.x, player->center.y, player->vert3.x, player->vert3.y, WHITE);
  DrawLine(player->vert3.x, player->vert3.y, player->vert1.x, player->vert1.y, WHITE);
}