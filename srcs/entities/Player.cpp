#include "entities/Player.hpp"

Player::Player(int id, int x, int y, Keyboard *keyboard)
    : AEntity(id, (t_rect){.pos = {x, y}, .width = PLAYER_SIZE, .height = PLAYER_SIZE}, PLAYER_SPEED), _keyboard(keyboard) {
}

Player::~Player() {
}

void Player::update(Map *map) {
    if (_keyboard->isActionActive(KEY_UP)) {
        move(map, 0, -speed);
        direction = 0;
    }
    if (_keyboard->isActionActive(KEY_RIGHT)) {
        move(map, speed, 0);
        direction = 1;
    }
    if (_keyboard->isActionActive(KEY_DOWN)) {
        move(map, 0, speed);
        direction = 2;
    }
    if (_keyboard->isActionActive(KEY_LEFT)) {
        move(map, -speed, 0);
        direction = 3;
    }
    // std::cout << "Player position: (" << hitbox.pos.x << ", " << hitbox.pos.y << ")" << std::endl;
}