/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:45:08 by rmakende          #+#    #+#             */
/*   Updated: 2025/01/14 19:52:31 by rmakende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*join_paths(const char *dir, const char *cmd)
{
	char	*joined_path;
	size_t	len_dir;
	char	*slash;
	char	*final_path;

	slash = "";
	if (!dir || !cmd)
		return (NULL);
	len_dir = ft_strlen(dir);
	if (dir[len_dir - 1] != '/')
		slash = "/";
	joined_path = ft_strjoin(dir, slash);
	if (!joined_path)
		return (NULL);
	final_path = ft_strjoin(joined_path, cmd);
	free(joined_path);
	if (!final_path)
		return (NULL);
	return (final_path);
}

char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) == envp[i])
			return (envp[i] + 5);
		i++;
	}
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
	i = -1;
	while (path_dirs[++i])
	{
		full_path = join_paths(path_dirs[i], cmd);
		if (!full_path || (access(full_path, X_OK) == 0))
			break ;
		free(full_path);
		full_path = NULL;
	}
	return (free_split(path_dirs), full_path);
}

char	**clean_arguments(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		args[i] = ft_cleaner(args[i], '\"');
		if (!args[i])
			return (NULL);
		args[i] = ft_cleaner(args[i], '\'');
		if (!args[i])
			return (NULL);
		i++;
	}
	return (args);
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
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	args = clean_arguments(args);
	path = find_command_path(args[0], envp);
	if (!path)
	{
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd("command not found\n", 2);
		free_split(args);
		exit(127);
	}
	execve(path, args, envp);
	free_split(args);
	free(path);
	exit(errno);
}
