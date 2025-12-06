/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebichan <ebichan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:41:07 by ebichan           #+#    #+#             */
/*   Updated: 2025/12/06 23:48:12 by ebichan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int option_check(t_cmd *cmd)
{
    if(ft_argv_len(cmd->argv) == 1)
        return(0);
    else if(cmd->argv[1][0] == '-')
        return(1);
    return(0);
}

int print_option_err(t_cmd *cmd)
{
    if(option_check(cmd))
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
        ft_putstr_fd(cmd->argv[1], STDERR_FILENO);
	    ft_putendl_fd(": invalid option", STDERR_FILENO);
        return(1);
    }
    return (0);
}
