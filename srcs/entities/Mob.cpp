#include "entities/Mob.hpp"

Mob::Mob(int id, int x, int y, AEntity* target)
    : AEntity(id, (t_rect){.pos = {x, y}, .width = MOB_SIZE, .height = MOB_SIZE}, MOB_SPEED), _target(target) {
        direction = _target->getDirection();
        setPosition(target->getPosition().x, target->getPosition().y);
}

Mob::~Mob() {
}

void Mob::update(Map *map) {
    t_veci target_pos;
    target_pos.x = _target->getPosition().x;
    target_pos.y = _target->getPosition().y;

    if (isCollidingWith(_target)){
        if (direction == 0)
            move(map, 0, speed);
        if (direction == 1)
            move(map, -speed, 0);
        if (direction == 2)
            move(map, 0, -speed);
        if (direction == 3)
            move(map, speed, 0);
    } else {
        if (target_pos.x )
        if (_target->getDirection() == 0)
            move(map, 0, -speed);
        if (_target->getDirection() == 1)
            move(map, speed, 0);
        if (_target->getDirection() == 2)
            move(map, 0, speed);
        if (_target->getDirection() == 3)
            move(map, -speed, 0);
    }

    

    // std::cout << "MOB position: (" << hitbox.pos.x << ", " << hitbox.pos.y << ")" << std::endl;
}