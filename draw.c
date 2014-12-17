/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 09:22:33 by ntrancha          #+#    #+#             */
/*   Updated: 2014/12/16 09:22:33 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mlx.h>
#include <libft.h>
#include "xwin.h"
#include "draw.h"

int		set_color(t_point *pt1, t_point *pt2)
{
	int	color;

	if (pt1->z == pt2->z && pt1->z > 0)
		color = 0xFF8222;
	else if (pt1->z == pt2->z)
		color = 0xFF0000;
	else
	{
		color = ft_rgb(255, 0, 255);
	}
	return (color);
}

void    parallele_next(t_point *p, t_tab *tab, t_win *data, int val, int zoom)
{
    int     decalx;
    int     decaly;
    int     hauteur;
    int     tmp_x;
    int     tmp_y;

    hauteur = 2;
    decalx = data->width - tab->line * (20 / tab->col);
    decaly = data->height - tab->col * (10 / tab->line);
    tmp_x = -1 * val * p->y + val * p->x;
    tmp_y = val * p->y + p->x;
    p->cx = decalx / hauteur + tmp_x * zoom;
    p->cy = decaly / hauteur + tmp_y * zoom - hauteur * p->z;
}

void    create_parallele(t_point *p, t_tab *tab, int c, int l, t_win *data)
{
    int     zoom;
    int     val;

    val = 4;
    zoom = 800 / val / (tab->line + tab->col);
    parallele_next(p, tab, data, val, zoom);
}

void    create_iso(t_point *p, t_tab *tab, int c, int c2, t_win *data)
{
	int	x;
	int	y;
	int	z;

	x = (p->x * data->zoom);
	y = (p->y * data->zoom);
	z = p->z * data->h;
	p->cx = (data->c * x) - (data->c2 * y) + ((data->c * tab->col * data->zoom) + data->width / 10);
	p->cy = (data->c / 2 * x) + (data->c2 / 2 * y) - z + (data->c * 2 * data->zoom) + data->height / 10;
	p->cz = p->cy - (data->c / 2 * x) + (data->c2 / 2 * y);
}

int     droite(t_win *data, t_point *p1, t_point *p2, int color)
{
    int x;

    if (p2->cx < p1->cx)
        return (droite(data, p2, p1, color));
    if (p1->cx == p2->cx && p1->cy == p2->cy)
        my_pixel_put_to_image(data->timg, p1->cx, p1->cy, set_color(p1, p2));
    else if (p1->cx == p2->cx)
    {
        x = p1->cy;
        while (x < p2->cy)
             my_pixel_put_to_image(data->timg, p1->cx, x++, set_color(p1, p2));
    }
    else if (p1->cy == p2->cy)
    {
        x = p1->cx;
        while (x < p2->cx)
             my_pixel_put_to_image(data->timg, x++, p2->cy, set_color(p1, p2));
    }
    else
    {
        x = p1->cx;
        while (x <= p2->cx)
            my_pixel_put_to_image(data->timg, x, p1->cy+((p2->cy-p1->cy)*((x++)-p1->cx))/(p2->cx-p1->cx), set_color(p1, p2));
    }
}
