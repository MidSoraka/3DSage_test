/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:16:34 by vlaine            #+#    #+#             */
/*   Updated: 2022/06/15 09:29:07 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOMNUKEM_H
# define DOOMNUKEM_H

# define INT_MAX 2147483647
# define X 0
# define Y 1
# define Z 2
# define R 0
# define G 1
# define B 2
# define W 0
# define A 1
# define S 2
# define D 3
# define KEY_M 109
# define KEY_R 114
# define KEY_I 105
# define KEY_O 111
# define KEY_ESC 65307
# define KEY_RIGHT 100
# define KEY_LEFT 97
# define KEY_UP 119
# define KEY_DOWN 115
# define KEY_SL 44
# define KEY_SR 46
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 3
# define MOUSE_MIDDLE_BUTTON 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5
# define BOOL int
# define TRUE 1
# define FALSE 0

# include <math.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "mlx/Linux/mlx.h"
# include <pthread.h>

typedef struct s_prm
{
	struct s_mlx		*mlx;
	struct s_player		*player;
}				t_prm;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*image_ptr;
	char		*image_add;
	int			size_line;
	int			erdian;
	int			bpp;
}				t_mlx;

typedef struct s_player
{
	int wasd[4];
	int sl,sr;
	int m;
	int x,y,z;
	int a;
	int l;
}	t_player;
void	open_window(t_prm *prm);
int		keyboard_input(int key, void *ptr);
int		mlx_window_loop(void *ptr);
int		key_up(int key, void *ptr);
int		key_down(int key, void *ptr);
void draw3D(t_prm *prm);

#endif
