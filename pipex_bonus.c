/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:26:56 by rmakende          #+#    #+#             */
/*   Updated: 2025/05/14 22:02:16 by rmakende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	if_forker(int fd[2], char *argv[], char **envp, int *i)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	execute_command(argv[*i], envp);
}

void	else_forker(int fd[2], pid_t pid)
{
	int	status;

	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	waitpid(pid, &status, 0);
}
int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		in_fd;
	int		out_fd;
    int     i;

	if (argc < 5)
		exit(1);
	in_fd = open(argv[1], O_RDONLY);
	out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
    i = 2;
	while (i < argc - 2)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
			if_forker(fd, argv, envp, &i);
		else
			else_forker(fd, pid);
        i++;
	}
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	execute_command(argv[argc - 2], envp);
	return (0);
}
