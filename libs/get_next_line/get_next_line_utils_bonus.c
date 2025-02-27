/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:03:58 by zelkalai          #+#    #+#             */
/*   Updated: 2024/02/15 12:50:13 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	newline_checker(t_list *list)
{
	int	i;

	if (list == NULL)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content[i] != '\0')
		{
			if (list->content[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

int	llist(t_list *list)
{
	int	i;
	int	l;

	l = 0;
	while (list)
	{
		i = 0;
		if (list == NULL)
			return (0);
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				l++;
				return (l);
			}
			i++;
			l++;
		}
		list = list->next;
	}
	return (l);
}

void	copy_the_list(t_list *list, char *the_line)
{
	int	i;
	int	j;

	j = 0;
	while (list)
	{
		i = 0;
		while (list->content[i] != '\0')
		{
			if (list->content[i] == '\n')
			{
				the_line[j] = '\n';
				the_line[++j] = '\0';
				return ;
			}
			the_line[j++] = list->content[i++];
		}
		list = list->next;
	}
	the_line[j] = '\0';
}

void	dealloc(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*tmp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean_node->content[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}
