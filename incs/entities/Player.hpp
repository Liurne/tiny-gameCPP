#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "entities/Entity.hpp"
# include "core/Keyboard.hpp"

class Player : public AEntity {
public:
    Player(int id, float x, float y, Keyboard *keyboard);
    ~Player();

    void update();

private:
    Player();
    Player(const Player&);
    Player& operator=(const Player&);

    Keyboard *_keyboard;

};

#endif