/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yebi <yebi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 01:34:49 by ebichan           #+#    #+#             */
/*   Updated: 2025/12/17 17:05:48 by yebi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_error(char *str)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (errno == ENOENT)
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
	else if (errno == EACCES)
		ft_putendl_fd("Permission denied", STDERR_FILENO);
	else if (errno == ENOTDIR)
		ft_putendl_fd("Not a directory", STDERR_FILENO);
	else if (errno == ENAMETOOLONG)
		ft_putendl_fd("File name too long", STDERR_FILENO);
	else if (errno == ENOMEM)
		ft_putendl_fd("Cannot allocate memory", STDERR_FILENO);
	else if (errno == EIO)
		ft_putendl_fd("Input/output error", STDERR_FILENO);
	else
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
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
	if (cmd->argv[1] && ft_strncmp(cmd->argv[1], "-", 2) != 0)
	{
		if (print_option_err(cmd))
			return (2);
	}
	if (ft_argv_len(cmd->argv) >= 3)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	return (0);
}

void	update_dir(t_data *data, char *old_pwd, char *new_path)
{
	if (old_pwd)
		update_env_var_cd(data, "OLDPWD", old_pwd);
	if (new_path)
		update_env_var_cd(data, "PWD", new_path);
}
