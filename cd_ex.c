/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_ex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yebi <yebi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:16:42 by ebichan           #+#    #+#             */
/*   Updated: 2025/12/08 11:59:58 by yebi             ###   ########.fr       */
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

static void	update_dir(t_data *data, char *old_pwd, char *new_path)
{
	if (old_pwd)
		update_env_var_cd(data, "OLDPWD", old_pwd);
	if (new_path)
		update_env_var_cd(data, "PWD", new_path);
}

static char	*get_base_pwd(t_data *data)
{
	char	*pwd;

	pwd = get_env_value("PWD", data);
	if (pwd)
		return (ft_strdup(pwd));
	return (getcwd(NULL, 0));
}

static int	exec_chdir(t_data *data, char *final_path, char *base_pwd)
{
	if (chdir(final_path) == -1)
	{
		cd_error(final_path);
		return (1);
	}
	update_dir(data, base_pwd, final_path);
	return (0);
}

int	builtin_cd(t_cmd *cmd, t_data *data)
{
	char	*target;
	char	*base_pwd;
	char	*final_path;
	int		ret;

	ret = check_cd_args(cmd);
	if (ret != 0)
		return (ret);
	target = set_cd_path(cmd, data);
	if (target == NULL)
		return (1);
	base_pwd = get_base_pwd(data);
	final_path = solve_logic_path(base_pwd, target);
	free(target);
	if (final_path == NULL)
	{
		free(base_pwd);
		return (1);
	}
	ret = exec_chdir(data, final_path, base_pwd);
	free(base_pwd);
	free(final_path);
	return (ret);
}
