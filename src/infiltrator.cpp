#include "infiltrator.h"
#include "ije02_game.h"

#define MAX_LIFE 100
Infiltrator::Infiltrator(vector<string> sprite_paths, unsigned id, double x, double y)
    : Character(sprite_paths, id, x, y, MAX_LIFE)
{
}

void
Infiltrator::heavy_attack()
{
    
}

void
Infiltrator::light_attack() {

}

void
Infiltrator::block() {

}

void
Infiltrator::special() {

}