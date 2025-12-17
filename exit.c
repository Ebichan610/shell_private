/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yebi <yebi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:57:11 by ebichan           #+#    #+#             */
/*   Updated: 2025/12/17 16:53:51 by yebi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	ft_atol(char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (sign == 1 && (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10
					&& (*str - '0') >= LLONG_MAX % 10)))
			return (2);
		if (sign == -1 && (result > -(LLONG_MIN / 10) || (result == -(LLONG_MIN
						/ 10) && (*str - '0') > -(LLONG_MIN % 10))))
			return (2);
		result = result * 10 + (long long)(*str - '0');
		str++;
	}
	return ((long)(result * sign));
}

static int	is_numeric(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (0);
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str != '\0')
		return (0);
	return (1);
}

static void	exit_err(t_cmd *cmd, t_data *data)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(cmd->argv[1], STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	if (data != NULL)
		free_all_data(data);
	exit(2);
}

static int	check_overflow(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		return (1);
	if (str[0] == '+')
		i++;
	while (str[i] == '0')
		i++;
	if (str[i] != '2')
		return (1);
	i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

int	builtin_exit(t_cmd *cmd, t_data *data)
{
	long	exit_status;

	if (isatty(STDIN_FILENO) && !cmd->is_in_child)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (ft_argv_len(cmd->argv) >= 2)
	{
		if (is_numeric(cmd->argv[1]) == 0)
			exit_err(cmd, data);
		exit_status = ft_atol(cmd->argv[1]);
		if (exit_status == 2 && check_overflow(cmd->argv[1]))
			exit_err(cmd, data);
		if (ft_argv_len(cmd->argv) >= 3)
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			return (1);
		}
		data->last_status = (int)(exit_status % 256);
	}
	if (data != NULL)
		free_all_data(data);
	exit(data->last_status);
	return (0);
}
