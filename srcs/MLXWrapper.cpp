/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MLXWrapper.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:58:04 by xcharra           #+#    #+#             */
/*   Updated: 2025/01/29 14:44:15 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLXWrapper.hpp"
#include <iostream>

MLXWrapper::MLXWrapper(int32_t width, int32_t height, bool resize) : _width(width), _height(height), _resize(resize), _mlx(NULL) {
	std::cout << "MLXSetup parametric constructor called" << std::endl;
}

MLXWrapper *MLXWrapper::operator()() { return (this); }

mlx_t *MLXWrapper::init() {
	_mlx = mlx_init(_width, _height, "fract-olCPP", _resize);
	if (!_mlx)
		throw std::runtime_error("Failed to initialize MLX library");
	return (_mlx);
}

mlx_image_t *MLXWrapper::newImage(int32_t width, int32_t height) {
	mlx_image_t	*newImage = mlx_new_image(_mlx, width, height);
	if (!newImage)
		throw std::runtime_error("Failed to initialize image");
	_images.push_back(newImage);
	return (newImage);
}

int32_t	MLXWrapper::imageToWindow(size_t i, int32_t x, int32_t y) const {
	if (i > _images.size())
		throw std::invalid_argument("Image index out of range");
	const int32_t	index = mlx_image_to_window(_mlx, _images[i], x, y);
	if (index == -1)
		throw std::runtime_error("Failed to put image to window");
	return (index);
}

void MLXWrapper::putPixel(size_t i, int32_t x, int32_t y, uint32_t color) const {
	if (i > _images.size())
		throw std::invalid_argument("Image index out of range");
	mlx_put_pixel(_images[i], x, y, color);
}

bool MLXWrapper::resizeImage(size_t i, uint32_t nwidth, uint32_t nheight) {
	if (i > _images.size())
		throw std::invalid_argument("Image index out of range");
	const bool	resized = mlx_resize_image(_images[i], nwidth, nheight);
	if (!resized)
		throw std::runtime_error("Failed to resize image");
	_width = _mlx->width;
	_height = _mlx->height;
	return (resized);
}

void MLXWrapper::loop() const {
	mlx_loop(_mlx);
}

bool MLXWrapper::loopHook(void(* f)(void*), void *param) const {
	bool	added = mlx_loop_hook(_mlx , f, param);
	if (!added)
		throw std::runtime_error("Failed to add loop hook");
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

int32_t MLXWrapper::getWidth() const { return (_width); }
int32_t MLXWrapper::getHeight() const { return (_height); }

//Useless constructors and operators
MLXWrapper::MLXWrapper() : _width(0), _height(0), _resize(false), _mlx(NULL), _images(0) {
	std::cout << "MLXSetup default constructor called" << std::endl;
}

MLXWrapper::MLXWrapper(MLXWrapper const &src) : _width(src._width), _height(src._height), _resize(src._resize), _mlx(src._mlx), _images(src._images) {
	std::cout << "MLXSetup default copy constructor called" << std::endl;

	(void)src;
	// *this = src;
}


MLXWrapper &MLXWrapper::operator=(MLXWrapper const &rhs) {
	std::cout << "MLXSetup assignment operator called" << std::endl;

	(void)rhs;
	// if (this != &rhs)
	// 	(void)rhs;
	return (*this);
}
