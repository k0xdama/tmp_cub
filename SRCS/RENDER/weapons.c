/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:58:18 by pmateo            #+#    #+#             */
/*   Updated: 2025/03/21 22:30:50 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

void	init_weapon(t_weapon *w, t_data *data)
{
	w->id = -1;
	w->xpm_nb = 4;
	w->sprites = yama(CREATE, NULL, sizeof(t_img) * (w->xpm_nb));
	w->state = IDLE;
	w->still_shooting = false;
	w->frame = 0;
	w->frame_counter_started = false;
	ft_bzero(&w->pos, sizeof(t_point));
	data->weapon = w;
}

void	get_weapons(t_weapon *w)
{
	int	i;
	float scale_factor;
	t_img tmp_sprites[4];

	i = 0;
	w->id = 1;
	// w->sprites[0] = xpm_to_mlx_img("./SPRITES/SPRITES_ARMORY/MP40/MP40_idle.xpm");
	// w->sprites[1] = xpm_to_mlx_img("./SPRITES/SPRITES_ARMORY/MP40/MP40_recoil1.xpm");
	// w->sprites[2] = xpm_to_mlx_img("./SPRITES/SPRITES_ARMORY/MP40/MP40_fire.xpm");
	// w->sprites[3] = xpm_to_mlx_img("./SPRITES/SPRITES_ARMORY/MP40/MP40_recoil2.xpm");
	tmp_sprites[0] = xpm_to_mlx_img("./SPRITES/SPRITES_ARMORY/MP40/MP40_idle.xpm");
	tmp_sprites[1] = xpm_to_mlx_img("./SPRITES/SPRITES_ARMORY/MP40/MP40_recoil1.xpm");
	tmp_sprites[2] = xpm_to_mlx_img("./SPRITES/SPRITES_ARMORY/MP40/MP40_fire.xpm");
	tmp_sprites[3] = xpm_to_mlx_img("./SPRITES/SPRITES_ARMORY/MP40/MP40_recoil2.xpm");
	while (i < 4)
	{
		scale_factor = (WIN_HEIGHT * 0.35) / tmp_sprites[i].height;
		w->sprites[i] = resize_img(scale_factor, &tmp_sprites[i]);
		i++;	
	}
	w->pos.x = (int)WIN_WIDTH / 3;
	w->pos.y = (int)WIN_HEIGHT / 1.50;
}

void	draw_weapon(int state, t_weapon *w, t_game *game)
{
	t_mlx *mlx;
	
	mlx = game->mlx;
	my_put_img_to_window(&w->sprites[state], &mlx->img, w->pos.x, w->pos.y);
	
}

void	render_weapon(t_game *game, t_weapon *w)
{
	if (w->state == SHOOTING && w->frame == 0)
		w->frame_counter_started = true;
	if (w->frame >= 0 && w->frame < FBS)
		draw_weapon(IDLE, w, game);
	else if (w->frame >= FBS && w->frame < (FBS * 2))
		draw_weapon(PREFIRE, w, game);
	else if (w->frame >= (FBS * 2) && w->frame < (FBS * 3 + 2))
		draw_weapon(SHOOTING, w, game);
	else if (w->frame >= (FBS * 3 + 2) && w->frame < (FBS * 4 + 2))
	{
		draw_weapon(POSTFIRE, w, game);
		if (game->keys->key_array[_SPACE] == 0)
			w->state = IDLE;
		if (w->state == IDLE && w->frame == (FBS * 4 + 1))
		{
			w->frame = 0;
			w->frame_counter_started = false;
		}
		else if (w->state == SHOOTING && w->frame == (FBS * 4 + 1))
			w->frame = (FBS * 2 - 1);
			
	}
	if (w->frame_counter_started == true)
		w->frame++;
}

//FBS = 3
// J'appuie sur espace -> rendre deux sprites (recoil1 et fire)
// 4 frame avant d'afficher recoil1 et 4 frame pour fire
// Je relache espace -> rendre deux sprite (recoil2 et retour a idle)
// 4 frame avant d'afficher recoil2 et 4 frame pour revenir a idle
// quand retour a idle remettre frame_counter a 0
//IDLE(0) + 4 = 4
//RECOIL1(4) + 4 = 8
//FIRE(8) + 4 = 12
//RECOIL2(12) = 16