#include <collision.c>

void UpdatePosition(ship* player, Matrix rotate){

  if(currentState.shootTime < currentState.shootDelay){
    currentState.shootTime += GetFrameTime();
  }
  if(currentState.spawnTime < currentState.spawnDelay){
    currentState.spawnTime += GetFrameTime();
  }

  //TODO: PlayerRotation
  //      ShootLaser
  //      ScoreCounter
  //      SpawnAsteroid

  if(IsKeyDown(KEY_W)){player->vert1.y -= 10;player->vert2.y -= 10;player->vert3.y -= 10;}
  if(IsKeyDown(KEY_S)){player->vert1.y += 10;player->vert2.y += 10;player->vert3.y += 10;}
  if(IsKeyDown(KEY_A)){player->vert1.x -= 10;player->vert2.x -= 10;player->vert3.x -= 10;}
  if(IsKeyDown(KEY_D)){player->vert1.x += 10;player->vert2.x += 10;player->vert3.x += 10;}

  if(IsKeyDown(KEY_UP)){
    player->vert1.x = player->center.x + (player->vert1.x - player->center.x)*cos(player->angle) - (player->vert1.y - player->center.y)*sin(player->angle);
    player->vert1.y = player->center.y + (player->vert1.x - player->center.x)*sin(player->angle) + (player->vert1.y - player->center.y)*cos(player->angle);

    player->vert2.x = player->center.x + (player->vert2.x - player->center.x)*cos(player->angle) - (player->vert2.y - player->center.y)*sin(player->angle);
    player->vert2.y = player->center.y + (player->vert2.x - player->center.x)*sin(player->angle) + (player->vert2.y - player->center.y)*cos(player->angle);

    player->vert3.x = player->center.x + (player->vert3.x - player->center.x)*cos(player->angle) - (player->vert3.y - player->center.y)*sin(player->angle);
    player->vert3.y = player->center.y + (player->vert3.x - player->center.x)*sin(player->angle) + (player->vert3.y - player->center.y)*cos(player->angle);
  }

  if(IsKeyDown(KEY_DOWN)){
    player->vert1.x = player->center.x + (player->vert1.x - player->center.x)*cos(-player->angle) - (player->vert1.y - player->center.y)*sin(-player->angle);
    player->vert1.y = player->center.y + (player->vert1.x - player->center.x)*sin(-player->angle) + (player->vert1.y - player->center.y)*cos(-player->angle);
                                                                                                                                             
    player->vert2.x = player->center.x + (player->vert2.x - player->center.x)*cos(-player->angle) - (player->vert2.y - player->center.y)*sin(-player->angle);
    player->vert2.y = player->center.y + (player->vert2.x - player->center.x)*sin(-player->angle) + (player->vert2.y - player->center.y)*cos(-player->angle);
                                                                                                                                             
    player->vert3.x = player->center.x + (player->vert3.x - player->center.x)*cos(-player->angle) - (player->vert3.y - player->center.y)*sin(-player->angle);
    player->vert3.y = player->center.y + (player->vert3.x - player->center.x)*sin(-player->angle) + (player->vert3.y - player->center.y)*cos(-player->angle);
  }

  /*if(IsKeyDown(KEY_DOWN)){
    player->vert1.x = player->center.x + (player->vert1.x - player->center.x)*cos(-player->angle) - (player->vert1.y - player->center.y)*sin(-player->angle);
    player->vert1.y = player->center.y + (player->vert1.x - player->center.x)*sin(-player->angle) + (player->vert1.y - player->center.y)*cos(-player->angle);
                                                                                                                                             
    player->vert2.x = player->center.x + (player->vert2.x - player->center.x)*cos(-player->angle) - (player->vert2.y - player->center.y)*sin(-player->angle);
    player->vert2.y = player->center.y + (player->vert2.x - player->center.x)*sin(-player->angle) + (player->vert2.y - player->center.y)*cos(-player->angle);
                                                                                                                                             
    player->vert3.x = player->center.x + (player->vert3.x - player->center.x)*cos(-player->angle) - (player->vert3.y - player->center.y)*sin(-player->angle);
    player->vert3.y = player->center.y + (player->vert3.x - player->center.x)*sin(-player->angle) + (player->vert3.y - player->center.y)*cos(-player->angle);
  }*/

  while(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && currentState.shootTime > currentState.shootDelay){
    if(currentState.laserCount >= MAXCOUNT){break;}
    laser beam = {
      .pos = GetMousePosition(),
    };
    currentState.laserArray[currentState.laserCount++] = beam;
    currentState.shootTime -= currentState.shootDelay;
  }
  DrawTriangleLines(player->vert1, player->vert2, player->vert3, WHITE);
}