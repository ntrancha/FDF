/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 20:03:20 by ntrancha          #+#    #+#             */
/*   Updated: 2014/12/16 20:03:20 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "recup.h"
#include "xwin.h"

t_tab       *check(char *file)
{
    char    *str;
    int     fd;
    t_tab   *tab;

    if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	str = NULL;
    ft_readfile(fd, &str);
    ft_strnrpl(&str, " ", "*", -1);
    ft_strnrpl(&str, "***", "*", -1);
    ft_strnrpl(&str, "**", "*", -1);
    tab = recup(str, '*');
    ft_tabup(tab, (ft_tabmin(tab) * -1));
	close(fd);
    ft_strdel(&str);
    return (tab);
}

void        config(t_win *win, int c, int c2, int zoom, int projection)
{
    win->c = c;
    win->c2 = c2;
    win->zoom = zoom;
    win->projection = projection;
	win->matrice = NULL;
}
