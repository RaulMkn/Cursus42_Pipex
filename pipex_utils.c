/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:45:08 by root              #+#    #+#             */
/*   Updated: 2024/12/10 21:31:17 by rmakende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*join_paths(const char *dir, const char *cmd)
{
	char	*joined_path;
	size_t	len_dir;
	size_t	len_cmd;

	len_dir = ft_strlen(dir);
	len_cmd = ft_strlen(cmd);
	joined_path = malloc(len_dir + len_cmd + 2);
	if (!joined_path)
		return (NULL);
	ft_strcpy(joined_path, dir);
	joined_path[len_dir] = '/';
	ft_strcpy(joined_path + len_dir + 1, cmd);
	return (joined_path);
}

char	*get_path_env(char **envp)
{
	char	*path_env;
	int		i;

	if (!envp)
		return (NULL);
	path_env = NULL;
	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (path_env);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	*full_path;
	char	*path_env;
	char	**path_dirs;
	int		i;

	if (!cmd || !*cmd || !envp)
		return (NULL);
	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	i = 0;
	while (path_dirs[i])
	{
		full_path = join_paths(path_dirs[i], cmd);
		if (!full_path)
			return (free_split(path_dirs), NULL);
		if (access(full_path, X_OK) == 0)
			return (free_split(path_dirs), full_path);
		free(full_path);
		i++;
	}
	return (free_split(path_dirs), NULL);
}

void	execute_command(char *cmd, char **envp)
{
	char	*path;
	char	**args;

	if (!cmd || !*cmd)
		exit(EXIT_FAILURE);
	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		free_split(args);
		exit(EXIT_FAILURE);
	}
	path = find_command_path(args[0], envp);
	if (!path)
	{
		free_split(args);
		exit(EXIT_FAILURE);
	}
	if (execve(path, args, envp) == -1)
	{
		free_split(args);
		free(path);
		exit(EXIT_FAILURE);
	}
}
