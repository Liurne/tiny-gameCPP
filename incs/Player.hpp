#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Entity.hpp"
#include "Keyboard.hpp"

class Player : public AEntity {
    public:
    Player(int id, float x, float y, Keyboard *keyboard);
    ~Player();

    void update() const override;

    private:
    Player();
    Player(const Player&);
    Player& operator=(const Player&);

    Keyboard *_keyboard;

};

#endif