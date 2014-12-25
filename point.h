/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 13:01:17 by ntrancha          #+#    #+#             */
/*   Updated: 2014/12/25 13:01:17 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

typedef struct  s_point
{
    int         x;
    int         y;
    int         z;
    int         cx;
    int         cy;
    int         cz;
}				t_point;

t_point *ft_pointnew(int x, int y, int z);
t_point *ft_pointcpy(t_point *p);
void    ft_pointdel(t_point *point);

#endif
