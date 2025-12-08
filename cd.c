/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yebi <yebi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:56:16 by ebichan           #+#    #+#             */
/*   Updated: 2025/12/08 12:00:03 by yebi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_cd_path(t_cmd *cmd, t_data *data)
{
	char	*path;

	if (ft_argv_len(cmd->argv) == 1)
	{
		path = get_env_value("HOME", data);
		if (path == NULL || ft_strlen(path) == 0)
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
			return (NULL);
		}
		return (ft_strdup(path));
	}
	if (ft_strncmp(cmd->argv[1], "-", 2) == 0)
	{
		path = get_env_value("OLDPWD", data);
		if (path == NULL)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
			return (NULL);
		}
		ft_putendl_fd(path, STDOUT_FILENO);
		return (ft_strdup(path));
	}
	return (ft_strdup(cmd->argv[1]));
}

static void	update_dir(t_data *data, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd != NULL)
	{
		if (old_pwd != NULL)
			update_env_var_cd(data, "OLDPWD", old_pwd);
		update_env_var_cd(data, "PWD", new_pwd);
		free(new_pwd);
	}
	else
		ft_putendl_fd("minishell: cd: error retrieving current directory",
			STDERR_FILENO);
}

int	builtin_cd(t_cmd *cmd, t_data *data)
{
	char	*path;
	char	*old_pwd;
	int		check_args;

	check_args = check_cd_args(cmd);
	if (check_args != 0)
		return (check_args);
	path = set_cd_path(cmd, data);
	if (path == NULL)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		cd_error(path);
		free(path);
		free(old_pwd);
		return (1);
	}
	update_dir(data, old_pwd);
	free(path);
	free(old_pwd);
	return (0);
}
