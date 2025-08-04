#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "entities/Entity.hpp"
# include "core/Keyboard.hpp"

class Player : public AEntity {
public:
    Player(int id, int x, int y, Keyboard *keyboard);
    ~Player();

    void update(Map *map);

private:
    Player();
    Player(const Player&);
    Player& operator=(const Player&);

    Keyboard *_keyboard;

};

#endif