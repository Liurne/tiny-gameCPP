#ifndef MLXWRAPPER_HPP
# define MLXWRAPPER_HPP

# include "include.h"
# include "error.h"

typedef std::vector<mlx_image_t *>	vecMLXImages;

class MLXWrapper {
public:
	MLXWrapper(int32_t width, int32_t height, bool resize);
	~MLXWrapper();
	MLXWrapper		*operator()();

	mlx_t		*init();
	void		loop() const;
	void		close();

	mlx_image_t	*newImage(int32_t width, int32_t height);
	mlx_image_t *newTexture(std::string path);
	int32_t		imageToWindow(mlx_image_t	*img, int32_t x, int32_t y) const;

	bool		loopHook(void(* f)(void*), void *param) const;
	void 		keyHook(mlx_keyfunc func, void *param) const;	
	void		resizeHook(mlx_resizefunc func, void *param) const;
	bool		isKeyDown(keys_t key) const;

	mlx_t		*getMlx() const { return _mlx; }
	mlx_image_t	*getImage(size_t i) const;

	int32_t		getWidth() const {return (_width);}
	int32_t		getHeight() const {return (_height);}

private:
	int32_t			_width;
	int32_t			_height;
	bool			_resize;
	mlx_t			*_mlx;
	vecMLXImages	_images;

	MLXWrapper();
	MLXWrapper(MLXWrapper const &src);
	MLXWrapper &operator=(MLXWrapper const &rhs);
};

#endif //MLXSETUP_HPP
