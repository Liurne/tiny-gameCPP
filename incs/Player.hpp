#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Entity.hpp"

class Player : public AEntity {
    public:
        Player();
        ~Player();
        Player(const Player&);
        Player& operator=(const Player&);

        void update() const override;

    private:

};

#endif