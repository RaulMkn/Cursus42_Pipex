/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:55:35 by rmakende          #+#    #+#             */
/*   Updated: 2024/12/10 21:55:49 by rmakende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

typedef struct {
    int flag;
    pid_t pid;
} returner;

returner	first_forker(int pipe_fd[2], int file_in, int file_out,
char **envp, char *argv[])
{
	pid_t	pid1;

	pid1 = fork();
	returner result = {1, pid1}
	if (pid1 == -1)
	{
		perror("Error al crear el proceso");
		close(file_in);
		close(file_out);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		dup2(file_in, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(file_in);
		close(file_out);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (result);
	}
	return (result);
}

returner	second_forker(int pipe_fd[2], int file_in, int file_out,
char **envp, char *argv[])
{
	pid_t	pid2;

	pid2 = fork();
	returner result = {1, pid1}
	if (pid2 == -1)
	{
		perror("Error al crear el proceso");
		close(file_in);
		close(file_out);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(file_out, STDOUT_FILENO);
		close(file_in);
		close(file_out);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		returner result = {1, pid1}
		return (result);
	}
	return (result);
}

void	pipex(int file_in, int file_out, char **envp, char *argv[])
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		close(file_in);
		close(file_out);
		exit(EXIT_FAILURE);
	}
	if(first_forker(pipe_fd, file_in, file_out, envp, argv).flag == 1)
		execute_command(argv[], env)
	if(second_forker(pipe_fd, file_in, file_out, envp, argv).flag == 1)
		execute_command(argv[], env)
	close(file_in);
	close(file_out);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char const *argv[], char **envp)
{
	int		file_in;
	int		file_out;
	char	**arg;

	arg = (char **)argv;
	if (argc != 5)
		exit(EXIT_FAILURE);
	file_in = open(argv[1], O_RDONLY);
	if (file_in < 0)
	{
		exit(EXIT_FAILURE);
	}
	file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_out < 0)
	{
		perror("Error al abrir file2");
		close(file_in);
		exit(EXIT_FAILURE);
	}
	pipex(file_in, file_out, envp, arg);
}
