/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_ex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebichan <ebichan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:56:25 by ebichan           #+#    #+#             */
/*   Updated: 2025/12/08 10:43:57 by ebichan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_pwd(t_cmd *cmd, t_data *data)
{
    char *pwd;
    char *cwd;

    if (print_option_err(cmd))
        return (1);
    pwd = get_env_value("PWD", data);
    if(pwd != NULL && ft_strlen(pwd) > 0)
        ft_putendl_fd(pwd, STDOUT_FILENO);
    else
    {
        cwd = getcwd(NULL, 0);
        if(cwd == NULL)
        {
            perror("minishell: pwd");
            return(1);
        }
        ft_putendl_fd(cwd, STDOUT_FILENO);
        free(cwd);
    }
    return(0);
}
