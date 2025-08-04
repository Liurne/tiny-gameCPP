#include "entities/Entity.hpp"

AEntity::AEntity(int id, t_rect hitbox, float speed)
    : id(id), hitbox(hitbox), speed(speed), direction(0), frame(0) {
}

AEntity::~AEntity() {
}

AEntity::AEntity(const AEntity &other)
    : id(other.id), hitbox(other.hitbox), speed(other.speed),
      direction(other.direction), frame(other.frame) {
}

AEntity& AEntity::operator=(const AEntity &other) {
    if (this != &other) {
        id = other.id;
        hitbox = other.hitbox;
        speed = other.speed;
        direction = other.direction;
        frame = other.frame;
    }
    return *this;
}

int AEntity::getId() const {
    return id;
}

void AEntity::setPosition(float x, float y) {
    hitbox.pos.x = x;
    hitbox.pos.y = y;
}

t_veci AEntity::getPosition() const {
    return hitbox.pos;
}

t_rect AEntity::getHitbox() const {
    return hitbox;
}

int AEntity::getDirection() const {
    return direction;
}

int AEntity::getFrame() const {
    return frame;
}

bool AEntity::move(Map *map, float dx, float dy) {
    t_veci cornerUL = {hitbox.pos.x, hitbox.pos.y};
    t_veci cornerDR = {cornerUL.x + hitbox.width, cornerUL.y + hitbox.height};
    t_veci cornerUR = {cornerDR.x, cornerUL.y};
    t_veci cornerDL = {cornerUL.x, cornerDR.y};
    t_veci newCornerUL = {cornerUL.x + dx, cornerUL.y + dy};
    t_veci newCornerDR = {cornerDR.x + dx, cornerDR.y + dy};
    t_veci newCornerUR = {newCornerDR.x, newCornerUL.y};
    t_veci newCornerDL = {newCornerUL.x, newCornerDR.y};

    if (map->isPositionValid(cornerUL, newCornerUL) &&
        map->isPositionValid(cornerUR, newCornerUR) &&
        map->isPositionValid(cornerDL, newCornerDL) &&
        map->isPositionValid(cornerDR, newCornerDR)) {
        setPosition(cornerUL.x, cornerUL.y);
        return true;
    }
    return false;
}

