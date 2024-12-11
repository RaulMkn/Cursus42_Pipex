/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:45:08 by root              #+#    #+#             */
/*   Updated: 2024/12/11 20:53:31 by rmakende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*join_paths(const char *dir, const char *cmd)
{
	char	*joined_path;
	size_t	len_dir;
	size_t	len_cmd;
	int		needs_slash;

	len_dir = ft_strlen(dir);
	len_cmd = ft_strlen(cmd);
	needs_slash = (dir[len_dir - 1] != '/');
	joined_path = malloc(len_dir + len_cmd + 1 + needs_slash);
	if (!joined_path)
		return (NULL);
	ft_strcpy(joined_path, dir);
	if (needs_slash)
		joined_path[len_dir] = '/';
	ft_strcpy(joined_path + len_dir + needs_slash, cmd);
	return (joined_path);
}

char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	return (envp[i] ? envp[i] + 5 : NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**path_dirs;
	char	*full_path;
	int		i;

	if (!cmd || !*cmd || !envp)
		return (NULL);
	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	full_path = NULL;
	i = 0;
	while (path_dirs[i])
	{
		full_path = join_paths(path_dirs[i], cmd);
		if (!full_path)
			break ;
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
		i++;
	}
	free_split(path_dirs);
	return (full_path);
}

void	execute_command(char *cmd, char **envp)
{
	char **args;
	char *path;
	
	if (!cmd || !*cmd)
		exit(EXIT_FAILURE);

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		free_split(args);
		perror("Error: comando vacío");
		exit(EXIT_FAILURE);
	}
	path = find_command_path(args[0], envp);
	if (!path)
	{
		perror("Error: comando no encontrado");
		free_split(args);
		exit(EXIT_FAILURE);
	}
	execve(path, args, envp);
	perror("Error: fallo en execve");
	free_split(args);
	free(path);
	exit(EXIT_FAILURE);
}
