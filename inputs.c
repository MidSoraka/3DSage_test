/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:54:18 by vlaine            #+#    #+#             */
/*   Updated: 2022/06/15 09:23:40 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

int	mlx_mouse_get_pos(void *win_ptr, int *x, int *y)
{
	*x = 0;
	*y = 0;

	return(1);
}

#include <stdio.h>

static void	keyboard_arrow_keys(int key, t_prm *prm)
{

}

static void	keyboard_input_extension(int key, t_prm *prm)
{

}

int	mouse_input(int key, int x, int y, void *ptr)
{

	return (0);
}

int	keyboard_input(int key, void *ptr)
{
	t_prm *prm;
	t_player *player;

	prm = (t_prm*)ptr;
	player = prm->player;
	return (0);
}

int key_up(int key, void *ptr)
{
	t_prm *prm;
	t_player *player;

	prm = (t_prm *)ptr;
	player = prm->player;
	int val = 0;
	if (key == KEY_UP)
		player->wasd[W] = val;
	if (key == KEY_LEFT)
		player->wasd[A] = val;
	if (key == KEY_DOWN)
		player->wasd[S] = val;
	if (key == KEY_RIGHT)
		player->wasd[D] = val;
	if (key == KEY_SL)
		player->sl = val;
	if (key == KEY_SR)
		player->sr = val;
	if (key == KEY_M)
		player->m = val;
	printf("key_up %d\n", key);
	return(0);
}

int key_down(int key, void *ptr)
{
	t_prm *prm;
	t_player *player;

	prm = (t_prm *)ptr;
	player = prm->player;
	int val = 1;
	if (key == KEY_UP)
		player->wasd[W] = val;
	if (key == KEY_LEFT)
		player->wasd[A] = val;
	if (key == KEY_DOWN)
		player->wasd[S] = val;
	if (key == KEY_RIGHT)
		player->wasd[D] = val;
	if (key == KEY_SL)
		player->sl = val;
	if (key == KEY_SR)
		player->sr = val;
	if (key == KEY_M)
		player->m = val;
	if (key == KEY_ENTER)
	{
		if (player->slowspeed != 1)
			player->slowspeed = 1;
		else
			player->slowspeed = 0;
	}
	if (key == KEY_ESC)
		exit(0);
	if (key == KEY_R)
		init(prm);
	printf("key_down'\n");
	return(0);
}