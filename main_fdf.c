/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fdf.c													:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/15 20:10:29 by ntrancha          #+#    #+#             */
/*   Updated: 2014/12/15 20:10:29 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "recup.h"
#include "config.h"
#include "includes/mlx.h"
#include <libft.h>
#include "xwin.h"
#include <fcntl.h>
#include <stdlib.h>
#include <mlx.h>
#include "draw.h"
#include "iso.h"
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "iso.h"

void	carre(t_win *data, t_point *p1, t_point *p12, t_point *p2, t_point *p22)
{
	int	x;
	int y;
	int	x2;
	int y2;
	t_point	*p3;
	t_point	*p4;

	x = p1->cx;
	x2 = p2->cx;
	while (x < p2->x)
	{
		y = p1->cy;
		y2 = p2->cy;
		while (y < p2->y)
		{
			p3 = ft_pointnew(x, y, p1->z);
			p4 = ft_pointnew(x2, y2, p2->z);
			droite(data, p3, p4, 0xFF0000);
			y++;
		}
		x++;
	}
}

void    remplire(t_win *data, t_tab *tab, int line, int col)
{
    int i;
    int j;
    t_point *p1;
    t_point *p2;
    t_point *p12;
    t_point *p22;

    i = 0;
    p2 = NULL;
    while (i + 1 < col)
    {
        j = 0;
        p2 = NULL;
        while (j + 1 < line)
		{
			p1 = ft_pointnew(j , i, tab->tab[i][j]);
			p12 = ft_pointnew(j , i, tab->tab[i][j]);
            create_iso(p1, tab, 6, 6, data);
            create_iso(p12, tab, 6, 6, data);
            if (p2 == NULL)
			{
                p2 = ft_pointcpy(p1);
				p22 = ft_pointcpy(p12);
			}
			carre(data, p1, p12, p2, p22);
            p2 = ft_pointcpy(p1);
            p22 = ft_pointcpy(p12);
			j++;
		}
		i++;
	}
}

void    dessine(t_win *data, t_tab *tab, t_point ***matrice)
{
    int i;
    int j;
    t_point *p1;
    t_point *p2;

    i = 0;
    while (i < tab->col)
    {
        j = 0;
        p2 = NULL;
        while (j < tab->line)
        {
            p1 = matrice[i][j];
            if (p2 == NULL)
                p2 = ft_pointcpy(p1);
            droite(data, p2, p1, 0xFFFFFF);
			ft_pointdel(p2);
            j++;
            p2 = ft_pointcpy(p1);
        }
        i++;
    }
	ft_pointdel(p2);
}

void    parcours(t_win *data, t_tab *tab, t_point ***matrice)
{
    int i;
    int j;
    t_point *p1;
    t_point *p2;

    j = 0;
    p1 = NULL;
    while (j < tab->line)
    {
        i = 0;
        p2 = NULL;
        while (i < tab->col)
        {
            p1 = data->matrice[i][j];
            if (p2 == NULL)
                p2 = ft_pointcpy(p1);;
            droite(data, p1, p2, 0xFFFFFF);
			ft_pointdel(p2);
            i++;
            p2 = ft_pointcpy(p1);;
        }
        j++;
    }
	ft_pointdel(p2);
}

int			main(int argc, char **argv)
{
	t_win	*win;
	
	if (argc != 2)
		return (-1);
	win = xwin_start(1480, 800, "42");
	if ((win->tab = check(argv[1])) == NULL)
		return (-1);
	config(win, 5, 5, 3, 1);
	win->h = 3;
	win->matrice = NULL;
	win->matrice = iso(win, win->tab);
    parcours(win, win->tab, win->matrice);
    dessine(win, win->tab, win->matrice);
    mlx_key_hook(win->win, key_hook, win);
    mlx_expose_hook(win->win, expose_hook, win);
    mlx_loop(win->ptr);
}
