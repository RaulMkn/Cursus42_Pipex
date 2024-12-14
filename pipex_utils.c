/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:45:08 by rmakende          #+#    #+#             */
/*   Updated: 2024/12/15 00:08:43 by rmakende         ###   ########.fr       */
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
	if (envp[i])
		return (envp[i] + 5);
	else
		return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	const char	*path_env = get_path_env(envp);
	char		**path_dirs;
	char		*full_path;
	int			i;

	if (!cmd || !*cmd || !envp)
		return (NULL);
	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	full_path = NULL;
	i = 0;
	while (path_dirs[i++])
	{
		full_path = join_paths(path_dirs[i], cmd);
		if (!full_path || (access(full_path, X_OK) == 0))
			break ;
		free(full_path);
		full_path = NULL;
	}
	return (free_split(path_dirs), full_path);
}

void	execute_command(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	if (!cmd || !*cmd)
		exit(126);
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
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		free_split(args);
		exit(127);
	}
	execve(path, args, envp);
	free_split(args);
	free(path);
	exit(errno);
}
