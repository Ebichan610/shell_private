/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yebi <yebi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:56:40 by ebichan           #+#    #+#             */
/*   Updated: 2025/12/17 16:54:00 by yebi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env(int remove_i, t_data *data)
{
	char	**new_envp;
	int		count;
	int		i;
	int		j;

	count = ft_argv_len(data->envp);
	new_envp = (char **)malloc(sizeof(char *) * count);
	if (new_envp == NULL)
		return ;
	i = 0;
	j = 0;
	while (i < count)
	{
		if (i == remove_i)
			free(data->envp[i]);
		else
			new_envp[j++] = data->envp[i];
		i++;
	}
	new_envp[j] = NULL;
	free(data->envp);
	data->envp = new_envp;
}

int	find_env(char *key, t_data *data)
{
	int		i;
	size_t	len;

	if (key == NULL || data->envp == NULL)
		return (-1);
	len = ft_strlen(key);
	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], key, len) == 0
			&& (data->envp[i][len] == '=' || data->envp[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

int	builtin_unset(t_cmd *cmd, t_data *data)
{
	int	i;
	int	env_i;

	i = 1;
	if (print_option_err(cmd))
		return (2);
	while (cmd->argv[i] != NULL)
	{
		env_i = find_env(cmd->argv[i], data);
		if (env_i != -1)
			remove_env(env_i, data);
		i++;
	}
	return (0);
}
