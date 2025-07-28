#ifndef ENTITY_HPP
# define ENTITY_HPP

# include "include.h"

class AEntity {
public:
    AEntity(int id, float x, float y, t_rect hitbox ,float speed = 1.0f);
    ~AEntity();
    AEntity(const AEntity&);
    AEntity& operator=(const AEntity&);

    virtual void    update() = 0;

    int     getId() const;

    void    setPosition(float x, float y);
    t_vecf  getPosition() const;
    t_rect  getHitbox() const;

    int     getDirection() const;
    int     getFrame() const;

protected:
    int     id;

    t_vecf  position;
    t_rect  hitbox;

    float   speed;

    int     direction; // 0: up, 1: right, 2: down, 3: left
    int     frame;

private:
    AEntity();

};

#endif