#ifndef ENTITY_H
#define ENTITY_H
#include "game.h"
int hostile_mobs_find_way(int mx, int my, int target_x, int target_y, int target_dimension);
void update_mobs_overworld();
void update_mobs_nether();
void check_attack_overworld();
void check_attack_nether();
#endif
