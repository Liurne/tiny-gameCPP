#include "core/MLXWrapper.hpp"

MLXWrapper::MLXWrapper(int32_t width, int32_t height, bool resize) : _width(width), _height(height), _resize(resize), _mlx(NULL) {

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

void MLXWrapper::close() {
	mlx_close_window(_mlx);
}

mlx_image_t *MLXWrapper::newImage(int32_t width, int32_t height) {
	mlx_image_t	*newImage = mlx_new_image(_mlx, width, height);
	if (!newImage)
		throw std::runtime_error(ERR_MLX_IMAGE);
	_images.push_back(newImage);
	return (newImage);
}

mlx_image_t *MLXWrapper::newTexture(std::string path) {
	mlx_texture_t* newTexture = mlx_load_png(path.c_str());
	if (!newTexture)
		throw std::runtime_error(ERR_MLX_TEXTURE);
	mlx_image_t* newImage = mlx_texture_to_image(_mlx, newTexture);
	mlx_delete_texture(newTexture);
	if (!newImage)
		throw std::runtime_error(ERR_MLX_IMAGE);
	_images.push_back(newImage);
	return (newImage);
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

void MLXWrapper::keyHook(mlx_keyfunc func, void *param) const {
	mlx_key_hook(_mlx, func, param);
}

void MLXWrapper::resizeHook(mlx_resizefunc func, void *param) const {
	mlx_resize_hook(_mlx, func, param);
}

void MLXWrapper::mouseHook(mlx_mousefunc func, void *param) const {
	mlx_mouse_hook(_mlx, func, param);
}

bool MLXWrapper::isKeyDown(const keys_t key) const {
	return (mlx_is_key_down(_mlx, key));
}

mlx_image_t *MLXWrapper::getImage(size_t i) const {
	if (i > _images.size())
		throw std::invalid_argument(ERR_MLX_IMAGE_INDEX);
	return _images[i];
}

MLXWrapper::~MLXWrapper() {
	if (_images.empty()) {
		for (size_t i = 0; i < _images.size(); ++i)
			mlx_delete_image(_mlx, _images[i]);
	}
	if (_mlx)
		mlx_terminate(_mlx);
}

//Unused

MLXWrapper::MLXWrapper() : _width(0), _height(0), _resize(false), _mlx(NULL), _images(0) {
}

MLXWrapper::MLXWrapper(MLXWrapper const &src) : _width(src._width), _height(src._height), _resize(src._resize), _mlx(src._mlx), _images(src._images) {
	(void)src;
}


MLXWrapper &MLXWrapper::operator=(MLXWrapper const &rhs) {
	(void)rhs;
	return (*this);
}
