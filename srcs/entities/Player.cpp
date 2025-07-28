#include "entities/Player.hpp"

Player::Player(int id, float x, float y, Keyboard *keyboard)
    : AEntity(id, x, y, (t_rect){.pos = {0, 0}, .width = 32, .height = 32}), _keyboard(keyboard) {
}

Player::~Player() {
}

void Player::update(){
    if (_keyboard->isActionActive(KEY_UP)) {
        setPosition(getPosition().x, getPosition().y - speed);
        direction = 0;
    } else if (_keyboard->isActionActive(KEY_RIGHT)) {
        setPosition(getPosition().x + speed, getPosition().y);
        direction = 1;
    } else if (_keyboard->isActionActive(KEY_DOWN)) {
        setPosition(getPosition().x, getPosition().y + speed);
        direction = 2;
    } else if (_keyboard->isActionActive(KEY_LEFT)) {
        setPosition(getPosition().x - speed, getPosition().y);
        direction = 3;
    }
}