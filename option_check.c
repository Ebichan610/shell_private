/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebichan <ebichan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:41:07 by ebichan           #+#    #+#             */
/*   Updated: 2025/12/03 16:16:47 by ebichan          ###   ########.fr       */
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
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd->argv[0], 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(cmd->argv[1], 2);
	    ft_putendl_fd(": invalid option", 2);
        return(1);
    }
    return (0);
}
