/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup.c	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/15 15:04:03 by ntrancha          #+#    #+#             */
/*   Updated: 2014/12/15 15:04:03 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "recup.h"

int     return_line(char *str)
{
    int ret;

    ret = 1;
    while (*str)
        if (*str++ == '\n')
            ret++;
    return (ret);
}

int     return_col(char *str, char c)
{
    int ret;
    int max;

    ret = 1;
    max = 1;
    while (*str)
    {
        if (ret > max)
            max = ret;
		if (*str == '\n')
			ret = 1;
        if (*str++ == c)
            ret++;
    }
    if (ret > max)
        max = ret;
    return (max);
}

static void	end(char *str, t_tab *tab, int *index, int *x, int *y)
{
	int		x1;
	int		y1;
	int		index1;

	x1 = *x;
	y1 = *y;
	index1 = *index;
	if (x1 >= tab->line || str[index1] == '\n')
    {
        *x = 0;
        (*y)++;
    }
	(*index)++;
}

t_tab		*recup(char *str, char c)
{
    t_tab	*tab;
    char	*tmp;
	int		index;
    int		x;
    int		y;

    x = 0;
    y = 0;
	index = 0;
    tmp = NULL;
    if ((tab = ft_tabnew(return_col(str, c), return_line(str))) == NULL)
		return (NULL);
    while (str[index] != '\0' && y <= tab->col)
    {
		ft_strdel(&tmp);
        tmp = ft_strdup("");
        while (str[index] != c && str[index] != '\0' && str[index] != '\n')
            ft_straddchar(&tmp, str[index++]);
		if (tmp != NULL)
    		tab->tab[y][x++] = ft_atoi(tmp);
	    ft_strdel(&tmp);
		end(str, tab, &index, &x, &y);
    }
	ft_strdel(&tmp);
    return (tab);
}
