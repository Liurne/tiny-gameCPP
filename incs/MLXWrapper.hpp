/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MLXWrapper.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:53:04 by xcharra           #+#    #+#             */
/*   Updated: 2025/02/24 14:38:25 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXWRAPPER_HPP
# define MLXWRAPPER_HPP

# include "../MLX/include/MLX42/MLX42.h"
# include <vector>

typedef std::vector<mlx_image_t *>	vecImages;

class MLXWrapper {
public:
	MLXWrapper(int32_t width, int32_t height, bool resize);
	~MLXWrapper();
	MLXWrapper		*operator()();

	mlx_t		*init();
	mlx_image_t	*newImage(int32_t width, int32_t height);
	int32_t		imageToWindow(size_t i, int32_t x, int32_t y) const;
	void		putPixel(size_t i, int32_t x, int32_t y, uint32_t color) const;
	bool		resizeImage(size_t i, uint32_t nwidth, uint32_t nheight);
	void		loop() const;

	bool		loopHook(void(* f)(void*), void *param) const;
	void		resizeHook(mlx_resizefunc func, void *param) const;
	bool		isKeyDown(keys_t key) const;

	mlx_t		*getMlx() const { return _mlx; }
	mlx_image_t	*getImage(size_t i) const { return _images[i]; }

	int32_t		getWidth() const;
	int32_t		getHeight() const;

private:
	int32_t		_width;
	int32_t		_height;
	bool		_resize;
	mlx_t		*_mlx;
	vecImages	_images;

	MLXWrapper();
	MLXWrapper(MLXWrapper const &src);
	MLXWrapper &operator=(MLXWrapper const &rhs);
};

#endif //MLXSETUP_HPP
