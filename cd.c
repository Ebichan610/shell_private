/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebichan <ebichan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:56:16 by ebichan           #+#    #+#             */
/*   Updated: 2025/12/06 23:46:23 by ebichan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int cd_error(char *path)
{
    ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
    ft_putstr_fd(path, 2);
    ft_putstr_fd(": ", 2);
    perror(path);
    return (1);
}

static void update_env_var(t_data *data, char *key, char *value)
{
    char *tmp;
    char *new_entry;

    if(key == NULL || value == NULL)
        return;
    tmp = ft_strjoin(key, "=");
    if(tmp == NULL)
        return;
    new_entry = ft_strjoin(tmp, value);
    free(tmp);
    if(new_entry == NULL)
        return;//ft_strjoin内のmallocエラーが伝播してここで処理する？
    env_deal(data, new_entry);
    free(new_entry);
}

int builtin_cd(t_cmd *cmd, t_data *data)
{
    char *path;
    char *old_pwd;
    char *new_pwd;

    if(ft_argv_len(cmd->argv) >= 3)
    {
        ft_putendl_fd("minishell: cd: too many arguments",STDERR_FILENO);
        return(1);
    }
    if(ft_argv_len(cmd->argv) == 1)
    {
        path = get_env_value("HOME", data);
        if(path == NULL || ft_strlen(path) == 0)
        {
            ft_putendl_fd("minishell: cd: HOME not set",STDERR_FILENO);
            if(path != NULL)
                free(path);
            return(1);
        }
    }
    else if(ft_argv_len(cmd->argv) == 2 &&ft_strncmp(cmd->argv[1], "-", 2) == 0)
    {
        path = ft_strdup(get_env_value("OLDPWD", data));
        if(path == NULL)
        {
            ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
            return(1);
        }
        ft_putendl_fd(path, 1);
    }
    else
        path = ft_strdup(cmd->argv[1]);
    old_pwd = getcwd(NULL, 0);
    if (chdir(path) == -1)
    {
        cd_error(path);
        free(path);
        free(old_pwd);
        return (1);
    }
    new_pwd = getcwd(NULL, 0);
    if (new_pwd != NULL)
    {
        update_env_var(data, "OLDPWD", old_pwd);
        update_env_var(data, "PWD", new_pwd);
        free(new_pwd);
    }
    else
        ft_putendl_fd("minishell: cd: error retrieving current directory", STDERR_FILENO);
    free(path);
    free(old_pwd);
    return (0);
}
