#include "raylib.h"
#include "sand.h"

void Collision(){
  for(int beamInd=0; beamInd<=currentState.laserCount; beamInd++){
    Laser* beam = &currentState.laserArray[beamInd];
    for(int astInd=0; astInd<=currentState.astCount; astInd++){
      Asteroid* ast = &currentState.astArray[astInd];
      if(CheckCollisionCircleLine(ast->pos, 25, beam->pos, (Vector2){beam->pos.x+beam->dir.x*10, beam->pos.y+beam->dir.y*10})){
        ast->destroyed = 1;
        ast->pos = (Vector2){0,0};
        ast->dir = (Vector2){0,0};
        ast->speed = 0;
        beam->hit = 1;
      }
    }
  }
}