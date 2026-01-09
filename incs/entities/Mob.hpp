#ifndef MOB_HPP
# define MOB_HPP

# include "entities/Entity.hpp"
# include "core/Keyboard.hpp"

class Mob : public AEntity {
public:
    Mob(int id, int x, int y, AEntity* target);
    ~Mob();

    void update(Map *map);

private:
    Mob();
    Mob(const Mob&);
    Mob& operator=(const Mob&);

    AEntity* _target;

};

#endif