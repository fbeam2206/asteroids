#ifndef SAND_H
#define SAND_H

#include <raylib.h>
#include <raymath.h>
#include <rcamera.h>

#define WIDTH 1200
#define HEIGHT 800
#define ACC 450
#define FRIC 450
#define MAXCOUNT 10
#define RADIUS 6
#define FLOOR 795
#define FONT_SIZE 48

#ifndef zero
  #define zero {0,0}
#endif
#ifndef xUnit
  #define xUnit {1,0}
#endif
#ifndef yUnit
  #define yUnit {0,1}
 #endif

typedef struct ship{
  Vector2 center;
  Vector2 vert1;
  Vector2 vert2;
  Vector2 vert3;
  Vector2 prevPos;
  Vector2 vel;
  Vector2 dir;
  float angle;
}ship;

typedef struct laser{
  Vector2 pos;
  Vector2 vel;
  Vector2 dir;
}laser;

typedef struct Asteroid{
  Vector2 pos;
  Vector2 prevPos;
  Vector2 vel;
  Vector2 dir;
}Asteroid;

typedef struct gameState{
  int laserCount;
  int astCount;
  float shootDelay;
  float shootTime;
  float spawnDelay;
  float spawnTime;
  Asteroid astArray[MAXCOUNT];
  laser laserArray[MAXCOUNT];
}gameState;

gameState currentState = {
  .laserCount = 0,
  .spawnDelay = 2,
  .shootDelay = 0.5 
};

void Collision(laser* beam, Asteroid* asteroid);

void UpdatePosition();

#endif