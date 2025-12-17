/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yebi <yebi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:56:10 by ebichan           #+#    #+#             */
/*   Updated: 2025/12/17 16:53:49 by yebi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_option_check(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->argv[i] != NULL)
	{
		j = 0;
		if (cmd->argv[i][j] != '-')
			return (i);
		else
		{
			j++;
			if (cmd->argv[i][j] == '\0')
				return (i);
			while (cmd->argv[i][j] == 'n')
				j++;
			if (cmd->argv[i][j] != '\0')
				return (i);
		}
		i++;
	}
	return (i);
}

int	builtin_echo(t_cmd *cmd, t_data *data)
{
	int	i;
	int	option_flag;

	(void)data;
	i = 1;
	option_flag = 1;
	if (cmd->argv[1] != NULL)
	{
		i = echo_option_check(cmd);
		option_flag = i;
		while (cmd->argv[i] != NULL)
		{
			ft_putstr_fd(cmd->argv[i], STDOUT_FILENO);
			if (cmd->argv[i + 1] != NULL)
				ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
		}
	}
	if (option_flag == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
