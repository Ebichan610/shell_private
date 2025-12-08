/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_ex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yebi <yebi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:56:25 by ebichan           #+#    #+#             */
/*   Updated: 2025/12/08 13:06:13 by yebi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_pwd_valid(char *pwd_val)
{
	struct stat	t_pwd;
	struct stat	t_cwd;

	if (pwd_val == NULL || pwd_val[0] != '/')
		return (0);
	if (stat(pwd_val, &t_pwd) == -1)
		return (0);
	if (stat(".", &t_cwd) == -1)
		return (0);
	if (t_pwd.st_ino == t_cwd.st_ino && t_pwd.st_dev == t_cwd.st_dev)
		return (1);
	return (0);
}

int	builtin_pwd(t_cmd *cmd, t_data *data)
{
	char	*pwd;
	char	*cwd;

	if (print_option_err(cmd))
		return (1);
	pwd = get_env_value("PWD", data);
	if (pwd != NULL && ft_strlen(pwd) > 0 && is_pwd_valid(pwd))
		ft_putendl_fd(pwd, STDOUT_FILENO);
	else
	{
		cwd = getcwd(NULL, 0);
		if (cwd == NULL)
		{
			perror("minishell: pwd");
			return (1);
		}
		ft_putendl_fd(cwd, STDOUT_FILENO);
		free(cwd);
	}
	return (0);
}
