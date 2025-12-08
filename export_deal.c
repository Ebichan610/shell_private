/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_deal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yebi <yebi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:58:01 by ebichan           #+#    #+#             */
/*   Updated: 2025/12/08 12:00:12 by yebi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_key_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		if (str[i] == '+' && str[i + 1] == '=')
			return (i);
		i++;
	}
	return (i);
}

static char	*create_clean_env(char *arg)
{
	char	*new_str;
	char	*plus_ptr;
	size_t	total_len;

	total_len = ft_strlen(arg);
	plus_ptr = ft_strnstr(arg, "+=", total_len);
	if (plus_ptr == NULL)
		return (ft_strdup(arg));
	new_str = (char *)malloc(sizeof(char) * total_len);
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, arg, (plus_ptr - arg) + 1);
	ft_strlcat(new_str, plus_ptr + 1, total_len);
	return (new_str);
}

static void	update_env_value(t_data *data, int i, char *arg, int append_flag)
{
	char	*new_entry;
	char	*val_start;

	val_start = ft_strchr(arg, '=');
	if (val_start == NULL)
		return ;
	val_start++;
	if (append_flag)
		new_entry = ft_strjoin(data->envp[i], val_start);
	else
		new_entry = create_clean_env(arg);
	if (new_entry == NULL)
		return ;
	free(data->envp[i]);
	data->envp[i] = new_entry;
}

static void	add_new_env(t_data *data, char *arg)
{
	char	**new_envp;
	char	*clean_arg;
	int		count;
	int		i;

	clean_arg = create_clean_env(arg);
	if (clean_arg == NULL)
		return ;
	count = ft_argv_len(data->envp);
	new_envp = (char **)malloc(sizeof(char *) * (count + 2));
	if (new_envp == NULL)
	{
		free(clean_arg);
		return ;
	}
	i = 0;
	while (i < count)
	{
		new_envp[i] = data->envp[i];
		i++;
	}
	new_envp[i] = clean_arg;
	new_envp[i + 1] = NULL;
	free(data->envp);
	data->envp = new_envp;
}

void	env_deal(t_data *data, char *arg)
{
	char	*key;
	int		i;
	int		append_flag;

	key = ft_substr(arg, 0, get_key_len(arg));
	if (key == NULL)
		return ;
	i = find_env(key, data);
	free(key);
	append_flag = 0;
	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
		append_flag = 1;
	if (i != -1)
		update_env_value(data, i, arg, append_flag);
	else
		add_new_env(data, arg);
}
