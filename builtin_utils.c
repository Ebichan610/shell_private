/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yebi <yebi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:51:22 by ebichan           #+#    #+#             */
/*   Updated: 2025/12/17 16:53:42 by yebi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_argv_len(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	free_split(char **result)
{
	int	i;

	i = 0;
	while (result[i] != NULL)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

void	ft_lst_del_last(t_list **lst, void (*del)(void *))
{
	t_list	*cur;
	t_list	*prv;

	if (!lst || !*lst)
		return ;
	cur = *lst;
	prv = NULL;
	while (cur->next)
	{
		prv = cur;
		cur = cur->next;
	}
	if (del)
		del(cur->content);
	free(cur);
	if (prv)
		prv->next = NULL;
	else
		*lst = NULL;
}
