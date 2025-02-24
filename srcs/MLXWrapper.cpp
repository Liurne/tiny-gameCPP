/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MLXWrapper.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:58:04 by xcharra           #+#    #+#             */
/*   Updated: 2025/02/24 15:42:43 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLXWrapper.hpp"

MLXWrapper::MLXWrapper(int32_t width, int32_t height, bool resize) : _width(width), _height(height), _resize(resize), _mlx(NULL) {
	std::cout << "MLXSetup parametric constructor called" << std::endl;
}

MLXWrapper *MLXWrapper::operator()() { return (this); }

mlx_t *MLXWrapper::init() {
	_mlx = mlx_init(_width, _height, "tiny-gameCPP", _resize);
	if (!_mlx)
		throw std::runtime_error(ERR_MLX_INIT);
	return (_mlx);
}

void MLXWrapper::loop() const {
	mlx_loop(_mlx);
}

int32_t	MLXWrapper::imageToWindow(mlx_image_t	*img, int32_t x, int32_t y) const {
	const int32_t	index = mlx_image_to_window(_mlx, img, x, y);
	if (index == -1)
		throw std::runtime_error(ERR_MLX_IMAGE_TO_WINDOW);
	return (index);
}

bool MLXWrapper::loopHook(void(* f)(void*), void *param) const {
	bool	added = mlx_loop_hook(_mlx , f, param);
	if (!added)
		throw std::runtime_error(ERR_MLX_LOOP_HOOK);
	return (added);
}

void MLXWrapper::resizeHook(mlx_resizefunc func, void *param) const {
	mlx_resize_hook(_mlx, func, param);
}

bool MLXWrapper::isKeyDown(const keys_t key) const {
	return (mlx_is_key_down(_mlx, key));
}

MLXWrapper::~MLXWrapper() {
	std::cout << "MLXSetup destructor called" << std::endl;

	if (_images.empty()) {
		for (size_t i = 0; i < _images.size(); ++i)
			mlx_delete_image(_mlx, _images[i]);
	}
	if (_mlx)
		mlx_terminate(_mlx);
}

//Useless constructors and operators
MLXWrapper::MLXWrapper() : _width(0), _height(0), _resize(false), _mlx(NULL), _images(0) {
	std::cout << "MLXSetup default constructor called" << std::endl;
}

MLXWrapper::MLXWrapper(MLXWrapper const &src) : _width(src._width), _height(src._height), _resize(src._resize), _mlx(src._mlx), _images(src._images) {
	std::cout << "MLXSetup default copy constructor called" << std::endl;

	(void)src;
}


MLXWrapper &MLXWrapper::operator=(MLXWrapper const &rhs) {
	std::cout << "MLXSetup assignment operator called" << std::endl;

	(void)rhs;
	return (*this);
}
