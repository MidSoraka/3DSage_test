/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:45:37 by vlaine            #+#    #+#             */
/*   Updated: 2022/06/14 11:14:03 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	open_window(t_prm *prm)
{
	t_mlx	*mlx;
	int		xy[2];

	mlx = prm->mlx;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, 800, 600, "win");
	mlx->image_ptr = mlx_new_image(mlx->mlx_ptr, 800, 600);
	mlx->image_add = \
	mlx_get_data_addr(mlx->image_ptr, &mlx->bpp, &mlx->size_line, &mlx->erdian);
	mlx_loop_hook(mlx->mlx_ptr, mlx_window_loop, prm);
	//mlx_key_hook(mlx->win_ptr, keyboard_input, prm);
//	mlx_mouse_hook(mlx->win_ptr, mouse_input, prm);
mlx_do_key_autorepeatoff(mlx->mlx_ptr);
	mlx_hook(mlx->win_ptr, 3, 3, key_up, prm);
	mlx_hook(mlx->win_ptr, 2, 2, key_down, prm);
	mlx_loop(mlx->mlx_ptr);
}
