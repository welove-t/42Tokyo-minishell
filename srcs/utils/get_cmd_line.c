/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 13:10:07 by terabu            #+#    #+#             */
/*   Updated: 2023/04/01 14:04:33 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_cmd(char *cmd);
static char	*get_path(char *cmd);
static int	get_env_index(const char *key, int index_start);

char	**get_cmd_array(char *cmd_line)
{
	char	**r_str_array;

	r_str_array = ft_split(cmd_line, ' ');
	if (ft_strchr(r_str_array[0], '/'))
		r_str_array[0] = get_path(r_str_array[0]);
	else
		r_str_array[0] = get_cmd(r_str_array[0]);
	return (r_str_array);
}

static char	*get_cmd(char *cmd)
{
	int		i_env_path;
	int		i;
	char	**path_array;
	char	*r_str_path;

	cmd = ft_strjoin("/", cmd);
	i_env_path = get_env_index("PATH=", 5);
	path_array = ft_split(&environ[i_env_path][5], ':');
	i = 0;
	while (path_array[i])
	{
		r_str_path = ft_strjoin(path_array[i], cmd);
		if (!access(r_str_path, X_OK))
			return (r_str_path);
		free(r_str_path);
		i++;
	}
	return (NULL);
}

static char	*get_path(char *cmd)
{
	if (!access(cmd, X_OK))
		return (cmd);
	return (NULL);
}

static int	get_env_index(const char *key, int index_start)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (!strncmp(environ[i], key, index_start))
			return (i);
		i++;
	}
	return (0);
}
