/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xwin.c												:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/15 14:25:59 by ntrancha          #+#    #+#             */
/*   Updated: 2014/12/15 14:25:59 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <mlx.h>
#include "xwin.h"
#include "iso.h"

t_img		*img_new(t_win *data, int width, int height)
{
    t_img   *img;

	if (data->img != NULL)
	{
		ft_strdel(&(data->timg->addr));
		ft_memdel(&data->timg->img);
		ft_memdel((void*)&data->timg);
	}
    if ((img = malloc(sizeof(t_img))) == NULL)
        return (NULL);
    if ((img->img = mlx_new_image(data->ptr, width * 4, height * 4)) == NULL)
        return (NULL);
    img->win = data;
    img->width = width;
    img->height = height;
    img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->lsize, &img->endian);
    data->img = img->img;
    data->timg = img;
	return (img);
}


t_win		*xwin_start(int width, int height, char *name)
{
	t_win	*data;
	t_img	*img;

	if ((data = malloc(sizeof(t_win))) == NULL || width < 1 || height < 1)
		return (NULL);
	data->img = NULL;
	data->timg = NULL;
    if ((data->ptr = mlx_init()) == NULL || name == NULL)
        return (NULL);
    if (!(data->win = mlx_new_window(data->ptr, width, height, name)))
        return (NULL);
    if ((img = img_new(data, width, height)) == NULL)
		return (NULL);
    data->img = img->img;
    data->timg = img;
	data->width = width;
	data->height = height;
	data->projection = 0;
	data->c = 0;
	data->c2 = 0;
	data->zoom= 0;
	data->x = 0;
	data->y = 0;
	data->z = 0;
	data->h = 0;
	data->angle = 0;
	data->mid_x = 0;
	data->mid_y = 0;
    return (data);
}

void    image_clean(t_win *win)
{
	int		x;
	int		y;

	x = 0;
	while (x <= win->width * 2)
	{
		y = 0;
		while (y < win->height * 2)
			my_pixel_put_to_image(win->timg, x, y++, ft_rgb(0, 0, 0)); 
		x++;
	}
}

void    my_pixel_put_to_image(t_img *img, int x, int y, int color)
{
    int             i;
    int             mask;
    char            tmp_clr;
    int             offset;

    i = 0;
    if (x >= 0 && x < img->width && y >= 0 && y < img->height)
    {
        while (i < (img->bpp / 8))
        {
            if (img->endian == 1)
                offset = img->bpp - 8 * (i + 1);
            else
                offset = 8 * i;
            mask = 0xFF << offset;
            tmp_clr = (color & mask) >> offset;
            img->addr[y * (img->lsize) + x * (img->bpp / 8) + i] = tmp_clr;
            i++;
        }
    }
}

int     expose_hook(t_win *win)
{
	if (win->z == 1)
	{
		win->matrice = iso(win, win->tab);
		img_new(win, win->width, win->height);
		parcours(win, win->tab, win->matrice);
	    dessine(win, win->tab, win->matrice);
		//mlx_clear_window(win->ptr, win->win);
		win->z = 0;
	}
    mlx_put_image_to_window(win->ptr, win->win, win->img, win->x, win->y);
    return (0);
}

int     key_hook(int k, t_win *e)
{
	ft_putendl(ft_itoa(k));
    if (k == 65361)
		e->x -= e->zoom * 6;
    if (k == 65363)
		e->x += e->zoom * 6;
    if (k == 65362)
		e->y -= e->zoom * 6;
    if (k == 65364)
		e->y += e->zoom * 6;
    if (k == 65451 && e->zoom < 9)
		e->zoom++;
    if (k == 65453 && e->zoom > 1)
		e->zoom--;
	if (k == 40)
        e->c2++;
	if (k == 45)
        e->c2--;
	if (k == 39)
        e->c++;
	if (k == 34)
        e->c--;
    if (k == 38)
		e->h++;
    if (k == 233)
		e->h--;
    if (k == 232)
		e->angle++;
    if (k == 95)
		e->angle--;
    if (k == 65307)
	{
		ft_strdel(&(e->timg->addr));
		ft_memdel(&e->timg->img);
		ft_memdel((void*)&e->timg);
		matriceclean(e);
		ft_tabdel(&(e->tab));
		mlx_destroy_window(e->ptr, e->win);
        exit(0);
	}
	if (k < 65361 || k > 65364)
		e->z = 1;
	expose_hook(e);
    return (0);
}
