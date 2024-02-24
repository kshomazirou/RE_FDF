/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshoma <kshoma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 08:09:33 by kshoma            #+#    #+#             */
/*   Updated: 2024/02/24 11:53:41 by kshoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	mod(float i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}

void	color_judge(int *color, t_fdf a, t_fdf b)
{
	if (b.z || a.z)
		*color = 0xfc0345;
	else
		*color = 0xBBFAFF;
	if (b.z != a.z)
		*color = 0xfc031c;
}

float	max_judge(float a, float b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

void	bresenham(t_fdf a, t_fdf b, t_fdf *data)
{
	float	x_step;
	float	y_step;
	float	max;
	int		color;

	set_param(&a, &b, data);
	x_step = b.x - a.x;
	y_step = b.y - a.y;
	max = max_judge(mod(x_step), mod(y_step));
	x_step /= max;
	y_step /= max;
	color_judge(&color, a, b);
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, a.x, a.y, color);
		a.x += x_step;
		a.y += y_step;
		if (a.x > data->win_x || a.y > data->win_y || a.y < 0 || a.x < 0)
			break ;
	}
}

void	draw(t_fdf **data)
{
	int	x;
	int	y;

	print_data(data[0][0]);
	y = 0;
	while (data[y])
	{
		x = 0;
		while (1)
		{
			if (data[y + 1])
				bresenham(data[y][x], data[y + 1][x], &data[0][0]);
			if (!data[y][x].is_last)
				bresenham(data[y][x], data[y][x + 1], &data[0][0]);
			if (data[y][x].is_last)
				break ;
			x++;
		}
		y++;
	}
}
