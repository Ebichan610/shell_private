/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebichan <ebichan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:57:02 by ebichan           #+#    #+#             */
/*   Updated: 2025/12/08 10:05:23 by ebichan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_env(t_cmd *cmd, t_data *data)
{
    int i;

    i = 0;
    if(print_option_err(cmd) == 1)
        return(1);
    if(ft_argv_len(cmd->argv) != 1)
    {
        ft_putendl_fd("minishell: env: too many arguments",STDERR_FILENO);
        return(1);
    }
    while(data->envp[i])
    {
        if(ft_strchr(data->envp[i], '='))
            ft_putendl_fd(data->envp[i],STDOUT_FILENO);
        i++;
    }
    return(0);
}
