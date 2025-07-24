#include "Keyboard.hpp"

Keyboard::Keyboard() {
    _actions[0] = (t_key){KEY_QUIT, MLX_KEY_ESCAPE, MLX_RELEASE};
    _actions[1] = (t_key){KEY_SCREENSHOT, MLX_KEY_Q, MLX_RELEASE};
    _actions[2] = (t_key){KEY_GENERATE_MAP, MLX_KEY_G, MLX_RELEASE};
    _actions[3] = (t_key){KEY_UP, MLX_KEY_W, MLX_RELEASE};
    _actions[4] = (t_key){KEY_DOWN, MLX_KEY_S, MLX_RELEASE};
    _actions[5] = (t_key){KEY_LEFT, MLX_KEY_A, MLX_RELEASE};
    _actions[6] = (t_key){KEY_RIGHT, MLX_KEY_D, MLX_RELEASE};
}

Keyboard::~Keyboard() {
    // Destructor logic if needed
}

void Keyboard::update(mlx_key_data_t keydata) {
    for (int i = 0; i < KEY_COUNT; ++i) {
        if (_actions[i].key == keydata.key)
            _actions[i].key_action = keydata.action;
    }
}

bool Keyboard::isActionActive(t_action action) const {
    if (action < 0 || action >= KEY_COUNT)
        return false; // Invalid action
    return (_actions[action].key_action == MLX_PRESS || _actions[action].key_action == MLX_REPEAT);
}