/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yebi <yebi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:15:40 by ebichan           #+#    #+#             */
/*   Updated: 2025/12/08 12:00:14 by yebi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	bubble_sort_env(char **env_arr, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - 1 - i)
		{
			if (ft_strncmp(env_arr[j], env_arr[j + 1], ft_strlen(env_arr[j])
					+ 1) > 0)
			{
				tmp = env_arr[j];
				env_arr[j] = env_arr[j + 1];
				env_arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export(char *str)
{
	int	i;

	i = 0;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	while (str[i] != '\0' && str[i] != '=')
	{
		ft_putchar_fd(str[i], 1);
		i++;
	}
	if (str[i] == '=')
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(&str[i + 1], STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	print_sorted_env(char **envp)
{
	char	**sorted_env;
	int		count;
	int		i;

	count = ft_argv_len(envp);
	sorted_env = (char **)malloc(sizeof(char *) * (count + 1));
	if (sorted_env == NULL)
		return ;
	i = 0;
	while (i < count)
	{
		sorted_env[i] = envp[i];
		i++;
	}
	bubble_sort_env(sorted_env, count);
	i = 0;
	while (i < count)
	{
		print_export(sorted_env[i]);
		i++;
	}
	free(sorted_env);
}
