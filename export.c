/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yebi <yebi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:56:35 by ebichan           #+#    #+#             */
/*   Updated: 2025/12/17 16:53:56 by yebi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '\0' || (ft_isalpha(arg[i]) == 0 && arg[i] != '_'))
		return (0);
	i++;
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (arg[i] == '+')
		{
			if (arg[i + 1] == '=')
				return (1);
			else
				return (0);
		}
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	print_export_err(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (1);
}

int	builtin_export(t_cmd *cmd, t_data *data)
{
	int	i;
	int	status;

	if (print_option_err(cmd))
		return (2);
	if (cmd->argv[1] == NULL)
	{
		print_sorted_env(data->envp);
		return (0);
	}
	i = 1;
	status = 0;
	while (cmd->argv[i] != NULL)
	{
		if (is_valid_identifier(cmd->argv[i]) == 0)
			status = print_export_err(cmd->argv[i]);
		else
			env_deal(data, cmd->argv[i]);
		i++;
	}
	return (status);
}
