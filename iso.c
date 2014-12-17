/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 20:18:24 by ntrancha          #+#    #+#             */
/*   Updated: 2014/12/16 20:18:24 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <math.h> 
#include "xwin.h"
#include <stdlib.h>
#include <unistd.h>

static t_point  ***tabnew(int line, int col)
{
    t_point     ***ptr;
    int         i;

    ptr = malloc(col * sizeof(t_point*));
    if(ptr == NULL)
        return (NULL);
    i = 0;
    while (i < col)
    {
        ptr[i] = malloc(line * sizeof(t_point**));
        if(ptr[i] == NULL)
            return (NULL);
        i++;
    }
    return (ptr);
}

void			matriceclean(t_win *data)
{
    int	     	i;
    int 	    j;
	
	i = 0;
	j = 0;
    while (j < data->tab->line)
    {
        i = 0;
        while (i < data->tab->col)
        {
            ft_pointdel(data->matrice[i][j]);
			i++;
        }
		j++;
	}
}

void	rot_matrix(t_point *p, t_win *data, float angle)
{
	float cs;
	float sn;

	sn = sin(angle);
	cs = cos(angle);
	p->cx = cs * (p->cx - data->tab->col * data->zoom) - sn * (p->cy - data->tab->line * data->zoom) + data->tab->col * data->zoom;
	p->cy = sn * (p->cx - data->tab->col * data->zoom) + cs * (p->cy - data->tab->line * data->zoom) + data->tab->line * data->zoom;
}

t_point     	***iso(t_win *data, t_tab *tab)
{
    int	     	i;
    int 	    j;
    t_point 	***matrice;
    t_point 	*p1;

    j = 0;
	if (data->matrice == NULL)
	    data->matrice = tabnew(tab->line, tab->col);
	else
		matriceclean(data);
    while (j < tab->line)
    {
        i = 0;
        while (i < tab->col)
        {
            p1 = ft_pointnew(j, i, tab->tab[i][j]);
            create_iso(p1, tab, data->c, data->c2, data);
			rot_matrix(p1, data, data->angle);
            data->matrice[i][j] = p1;
            i++;
        }
        j++;
    }
    return (data->matrice);
}
