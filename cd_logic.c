/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_logic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yebi <yebi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 01:37:49 by ebichan           #+#    #+#             */
/*   Updated: 2025/12/17 16:53:45 by yebi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_path_segment(char *path, char *segment)
{
	char	*tmp;
	char	*new_path;

	tmp = ft_strjoin(path, "/");
	free(path);
	if (tmp == NULL)
		return (NULL);
	new_path = ft_strjoin(tmp, segment);
	free(tmp);
	return (new_path);
}

static char	*rebuild_path(t_list *stack)
{
	char	*path;

	path = ft_strdup("");
	if (path == NULL)
		return (NULL);
	while (stack != NULL)
	{
		path = append_path_segment(path, (char *)stack->content);
		if (path == NULL)
			return (NULL);
		stack = stack->next;
	}
	if (ft_strlen(path) == 0)
	{
		free(path);
		return (ft_strdup("/"));
	}
	return (path);
}

static int	process_token(char **tokens, t_list **stack)
{
	int		i;
	t_list	*node;
	char	*str;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (ft_strncmp(tokens[i], "..", 3) == 0)
			ft_lst_del_last(stack, free);
		else if (ft_strncmp(tokens[i], ".", 2) != 0)
		{
			str = ft_strdup(tokens[i]);
			if (str == NULL)
				return (0);
			node = ft_lstnew(str);
			if (node == NULL)
			{
				free(str);
				return (0);
			}
			ft_lstadd_back(stack, node);
		}
		i++;
	}
	return (1);
}

static char	*join_paths(char *base, char *dst)
{
	char	*tmp;
	char	*full;

	if (dst[0] == '/')
		return (ft_strdup(dst));
	tmp = ft_strjoin(base, "/");
	if (tmp == NULL)
		return (NULL);
	full = ft_strjoin(tmp, dst);
	free(tmp);
	return (full);
}

char	*solve_logic_path(char *base, char *dst)
{
	char	*full_path;
	char	**tokens;
	t_list	*stack;
	char	*result;

	if (base == NULL || dst == NULL)
		return (NULL);
	full_path = join_paths(base, dst);
	if (full_path == NULL)
		return (NULL);
	tokens = ft_split(full_path, '/');
	free(full_path);
	if (tokens == NULL)
		return (NULL);
	stack = NULL;
	if (process_token(tokens, &stack) == 0)
	{
		free_split(tokens);
		ft_lstclear(&stack, free);
		return (NULL);
	}
	result = rebuild_path(stack);
	free_split(tokens);
	ft_lstclear(&stack, free);
	return (result);
}
