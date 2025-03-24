/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_mlx_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:35:26 by annabrag          #+#    #+#             */
/*   Updated: 2025/03/21 04:08:04 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static	void	__copy_non_tr_pixel(t_img *src, t_img *dest, t_point src_pos, t_point dest_pos)
{
	int	src_pixel;
	int	dest_pixel;

	src_pixel = (src_pos.y * src->size_line) + (src_pos.x * 4);
	dest_pixel = (dest_pos.y * dest->size_line) + (dest_pos.x * 4);
	// printf("src ? %d\n", *(int *)(src->addr + pixel));
	if ((uint32_t)*(int *)(src->addr + src_pixel) == 0xFF000000)
	{
		// printf("degage\n");
		return ;
	}
	else
	{
		*(int *)(dest->addr + dest_pixel) = *(int *)(src->addr + src_pixel);
		// printf("bienvenue a toi %d\n", *(int *)(dest->addr + pixel));

	}
}

void	blit_transparent_img(t_img *src, t_img *dest, int pos_x, int pos_y)
{
	t_point src_px_pos;
	t_point dest_px_pos;
	int	x;
	int	y;

	y = 0;
	while (y < src->height)
	{
		x = 0;
		while (x < src->width)
		{
			src_px_pos.x = x;
			src_px_pos.y = y;
			dest_px_pos.x = x + pos_x;
			dest_px_pos.y = y + pos_y;
			__copy_non_tr_pixel(src, dest, src_px_pos, dest_px_pos);
			x++;
		}
		y++;
	}
	return ;
}

void	my_put_img_to_window(t_img *src, t_img *dest, int pos_x, int pos_y)
{
	blit_transparent_img(src, dest, pos_x, pos_y);
}

void	my_pixel_put_to_img(t_img *img, int color, int x, int y)
{
	int	pixel;

	pixel = (y * img->size_line) + (x * 4);
	if (img->endian == 0)
	{
		img->addr[pixel] = (color) & 0xFF;
		img->addr[pixel + 1] = (color >> 8) & 0xFF;
		img->addr[pixel + 2] = (color >> 16) & 0xFF;
		img->addr[pixel + 3] = (color >> 24) & 0xFF;
	}
	else if (img->endian == 1)
	{
		img->addr[pixel] = (color >> 24);
		img->addr[pixel + 1] = (color >> 16) & 0xFF;
		img->addr[pixel + 2] = (color >> 8) & 0xFF;
		img->addr[pixel + 3] = (color) & 0xFF;
	}
}

void	clear_img(t_img *img, size_t size_x, size_t size_y, int color)
{
	t_point	pixel;

	if (img->addr == NULL)
		return ;
	pixel.y = 0;
	while (pixel.y < size_y)
	{
		pixel.x = 0;
		while (pixel.x < size_x)
		{
			my_pixel_put_to_img(img, color, pixel.x, pixel.y);
			pixel.x++;
		}
		pixel.y++;
	}
	return ;
}

