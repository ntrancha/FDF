/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 12:59:37 by ntrancha          #+#    #+#             */
/*   Updated: 2014/12/25 12:59:37 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "point.h"

t_point     *ft_pointnew(int x, int y, int z)
{
    t_point *p;

    p = malloc(sizeof(t_point));
    if (p == NULL)
        return (NULL);
    p->x = x;
    p->y = y;
    p->z = z;
    p->cx = x;
    p->cy = y;
    p->cz = z;
    return (p);
}

void        ft_pointdel(t_point *point)
{
    ft_memdel((void*)&point);
}

t_point     *ft_pointcpy(t_point *p)
{
    t_point *cpy;

    cpy = malloc(sizeof(t_point));
    if (cpy == NULL)
        return (NULL);
    cpy->x = p->x;
    cpy->y = p->y;
    cpy->z = p->z;
    cpy->cx = p->cx;
    cpy->cy = p->cy;
    cpy->cz = p->cz;
    return (cpy);
}
