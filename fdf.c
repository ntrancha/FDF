/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/18 18:48:12 by ycribier          #+#    #+#             */
/*   Updated: 2013/12/23 21:07:45 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "fdf.h"
#include "libft.h"

int		get_ltab_size(char **tab)
{
	int		size;

	size = 0;
	if (tab)
	{
		while (*tab)
		{
			size++;
			tab++;
		}
	}
	return (size);
}

void	clean_line(char *line)
{
	if (line)
	{
		while (*line)
		{
			if (!(*line >= '0' && *line <= '9') && *line != '-' && *line != '+')
				*line = ' ';
			line++;
		}
	}
}

void	check_list(t_list *list, int *nb_col)
{
	char	*line;
	int		line_size;
	char	**tab;

	while (list)
	{
		line = (char *)(list->content);
		clean_line(line);
		tab = ft_strsplit(line, ' ');
		line_size = get_ltab_size(tab);
		if (line_size > *nb_col)
			*nb_col = line_size;
		list = list->next;
		free(tab);
	}
}

void	delete_list(t_list **alst)
{
	t_list	*tmp;
	t_list	*begin_lst;

	if (alst)
	{
		begin_lst = *alst;
		while ((*alst) != NULL)
		{
			free((*alst)->content);
			tmp = *alst;
			free(*alst);
			*alst = (tmp)->next;
		}
		begin_lst = NULL;
	}
}

void	fdf(int fd, t_env *e)
{
	char	*line;
	t_list	*list;
	t_list	*elem;
	int		nb_col;
	int		nb_line;
	int		ret;

	line = NULL;
	list = NULL;
	nb_line = 0;
	nb_col = 0;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		elem = ft_lstnew(line, (ft_strlen(line) + 1) * sizeof(char));
		ft_lstpush(&list, elem);
		free(line);
		nb_line++;
	}
	if (ret == -1)
	{
		perror("[GNL]: Error reading file.");
		exit(-1);
	}
	check_list(list, &nb_col);
	manage_vtx_tab(e, list, nb_line, nb_col);
	delete_list(&list);
}
