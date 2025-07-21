#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include "include.h"

const int KEY_COUNT = 7;

typedef enum e_action{
    KEY_QUIT,
    KEY_SCREENSHOT,
    KEY_GENERATE_MAP,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
} t_action;

typedef struct s_key {
    t_action    action_type;
    keys        key;
    action_t    key_action;
} t_key;

class Keyboard {
public:
    Keyboard();
    ~Keyboard();

    void update(mlx_key_data_t keydata);

    bool isActionActive(t_action action) const;


    private:
    Keyboard(const Keyboard&);
    Keyboard& operator=(const Keyboard&);

    t_key _actions[KEY_COUNT];
};


#endif