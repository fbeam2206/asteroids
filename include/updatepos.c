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

  if(IsKeyDown(KEY_DOWN)){
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