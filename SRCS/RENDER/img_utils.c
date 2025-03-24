/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_xpm_from_img.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:33:51 by art3mis           #+#    #+#             */
/*   Updated: 2025/03/04 15:28:50 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	build_resized_img(float scale_factor, t_img *src, t_img *dest)
{
	t_point src_px_pos;
	t_point dest_px_pos;
	int	src_pixel;
	int	dest_pixel;

	dest_px_pos.y = 0;
	while (dest_px_pos.y < dest->height)
	{
		dest_px_pos.x = 0;
		while (dest_px_pos.x < dest->width)
		{
			src_px_pos.x = (int)(dest_px_pos.x / scale_factor);
			src_px_pos.y = (int)(dest_px_pos.y / scale_factor);
			src_pixel = (src_px_pos.y * src->size_line) + (src_px_pos.x * 4);
			dest_pixel = (dest_px_pos.y * dest->size_line) + (dest_px_pos.x * 4);
			// if ((uint32_t)*(int *)(src->addr + src_pixel) != 0xFF000000)
			*(int *)(dest->addr + dest_pixel) = *(int *)(src->addr + src_pixel);
			dest_px_pos.x++;
		}
		dest_px_pos.y++;
	}
}

t_img	resize_img(float scale_factor, t_img *to_resize)
{
	t_img 	resized;
	int		new_width = to_resize->width * scale_factor;
	int		new_height = to_resize->height * scale_factor;

	resized.img_ptr = mlx_new_image(s_mlx()->mlx_ptr, new_width, new_height);
	resized.addr = mlx_get_data_addr(resized.img_ptr, &resized.bits_per_pixel, &resized.size_line, &resized.endian);
	resized.width = new_width;
	resized.height = new_height;
	build_resized_img(scale_factor, to_resize, &resized);
	mlx_destroy_image(s_mlx()->mlx_ptr, to_resize->img_ptr);
	return (resized);
}

t_img	xpm_to_mlx_img(char *relative_path)
{
	t_img	img;

	ft_memset(&img, 0, sizeof(t_img));
	img.img_ptr = mlx_xpm_file_to_image(s_mlx()->mlx_ptr, relative_path,
			&img.width,
			&img.height);
	if (img.img_ptr == NULL)
	{
		err_msg("minilibX", ERR_XPM);
		return (img);
	}
	img.addr = mlx_get_data_addr(img.img_ptr,
		&img.bits_per_pixel,
		&img.size_line,
		&img.endian);
	if (img.addr == NULL)
	{
		err_msg("minilibX", ERR_ADDR);
		del_img(s_mlx(), img.img_ptr);
		ft_memset(&img, 0, sizeof(t_img));
	}
	return (img);
}
