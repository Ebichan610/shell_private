/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_ex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yebi <yebi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 01:34:49 by ebichan           #+#    #+#             */
/*   Updated: 2025/12/08 11:59:54 by yebi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	perror(path);
	return (1);
}

void	update_env_var_cd(t_data *data, char *key, char *value)
{
	char	*tmp;
	char	*new_entry;

	if (key == NULL || value == NULL)
		return ;
	tmp = ft_strjoin(key, "=");
	if (tmp == NULL)
		return ;
	new_entry = ft_strjoin(tmp, value);
	free(tmp);
	if (new_entry == NULL)
		return ;
	env_deal(data, new_entry);
	free(new_entry);
}

int	check_cd_args(t_cmd *cmd)
{
	if (ft_argv_len(cmd->argv) >= 3)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (cmd->argv[1] && ft_strncmp(cmd->argv[1], "-", 2) != 0)
	{
		if (print_option_err(cmd))
			return (2);
	}
	return (0);
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
