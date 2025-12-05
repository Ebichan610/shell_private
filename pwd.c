/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebichan <ebichan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:56:25 by ebichan           #+#    #+#             */
/*   Updated: 2025/12/03 16:13:35 by ebichan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_pwd(t_cmd *cmd, t_data *data)
{
    char *cwd;

    if (print_option_err(cmd))
        return (1);
    cwd = get_env_value("PWD", data);//getcwdにするかどうか
    if(cwd == NULL)
    {
        perror("minishell: pwd");
        return(1);
    }
    printf("%s\n", cwd);
    free(cwd);
    return(0);
}
