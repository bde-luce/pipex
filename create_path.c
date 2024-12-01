/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:49:10 by bde-luce          #+#    #+#             */
/*   Updated: 2024/11/12 23:49:10 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_array(char	**arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	error_exec(char *path, char **arr_arg, char *function)
{
	write(2, function, ft_strlen(function));
	write(2, ": command not found\n", 20);
	free(path);
	free_array(arr_arg);
	exit(1);
}

void	exec_command(char *command, char **envp)
{
	char	**arr_arg;
	char	*path;

	arr_arg = ft_split(command, ' ');
	path = create_path(arr_arg[0], envp);
	if (execve(path, arr_arg, envp) == -1)
		error_exec(path, arr_arg, arr_arg[0]);
}

static char	**find_path(char **envp)
{
	int		i;
	char	*path_trim;
	char	**path_env;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", sizeof(char) * 5) == 0)
		{
			path_trim = ft_strtrim(envp[i], "PATH=");
			path_env = ft_split(path_trim, ':');
			free(path_trim);
			return (path_env);
		}
		i++;
	}
	return (NULL);
}

char	*create_path(char *function, char **envp)
{
	int		i;
	char	**path_env;
	char	*path_join;
	char	*path;

	path_env = find_path(envp);
	i = 0;
	while (path_env && path_env[i])
	{
		path_join = ft_strjoin(path_env[i], "/");
		path = ft_strjoin(path_join, function);
		free(path_join);
		if (access(path, X_OK) == 0)
		{
			free_array(path_env);
			return (path);
		}
		free(path);
		i++;
	}
	write(2, "Error not able to execute or find function\n", 43);
	free_array(path_env);
	return (NULL);
}
