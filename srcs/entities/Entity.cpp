#include "entities/Entity.hpp"

AEntity::AEntity(int id, t_rect hitbox, float speed)
    : id(id), hitbox(hitbox), speed(speed), direction(0), frame(0), view(NULL) {
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

void AEntity::setPosition(int x, int y) {
    hitbox.pos.x = x;
    hitbox.pos.y = y;
    if (view) {
        view->instances[0].x = x;
        view->instances[0].y = y;
    }
}

void AEntity::setView(mlx_image_t *newView) {
    this->view = newView;
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

bool AEntity::isCollidingWith(AEntity *target){

    return !(
            hitbox.pos.x + hitbox.width  <= target->hitbox.pos.x
            || target->hitbox.pos.x + target->hitbox.width <= hitbox.pos.x
            || hitbox.pos.y + hitbox.height <= target->hitbox.pos.y
            || target->hitbox.pos.y + target->hitbox.height <= hitbox.pos.y
        );
}

bool AEntity::move(Map *map, int dx, int dy) {
    t_veci cornerUL = {hitbox.pos.x, hitbox.pos.y};
    t_veci cornerDR = {cornerUL.x + hitbox.width - 1, cornerUL.y + hitbox.height - 1};
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
        setPosition(newCornerUL.x, newCornerUL.y);
        return true;
    }
    return false;
}

