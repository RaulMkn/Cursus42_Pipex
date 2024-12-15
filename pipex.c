/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:55:35 by rmakende          #+#    #+#             */
/*   Updated: 2024/12/15 16:49:42 by rmakende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_forker(int pipe_fd[2], int in, char *argv, char **envp)
{
	if (dup2(in, STDIN_FILENO) == -1 || dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("Error en dup2 (primer fork)");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(in);
	execute_command(argv, envp);
	exit(EXIT_FAILURE);
}

void	second_forker(int pipe_fd[2], int out, char *argv, char **envp)
{
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1 || dup2(out, STDOUT_FILENO) == -1)
	{
		perror("Error en dup2 (segundo fork)");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(out);
	execute_command(argv, envp);
	exit(EXIT_FAILURE);
}

void	handle_child_status(pid_t pid, int *final_exit_code)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
	*final_exit_code = (status >> 8);
}

int	pipex(int file_in, int file_out, char **envp, char *argv[])
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		exit_code;

	if (pipe(pipe_fd) == -1)
		exit(EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == -1)
		exit(EXIT_FAILURE);
	if (pid1 == 0)
		first_forker(pipe_fd, file_in, argv[2], envp);
	pid2 = fork();
	if (pid2 == -1)
		exit(EXIT_FAILURE);
	if (pid2 == 0)
		second_forker(pipe_fd, file_out, argv[3], envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	handle_child_status(pid1, &exit_code);
	handle_child_status(pid2, &exit_code);
	return (exit_code);
}

int	main(int argc, char const *argv[], char **envp)
{
	int	file_in;
	int	file_out;
	int	exit_code;

	if (argc != 5)
	{
		fprintf(stderr, "Uso: %s file1 cmd1 cmd2 file2\n", argv[0]);
		return (EXIT_FAILURE);
	}
	file_in = open(argv[1], O_RDONLY);
	file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_in < 0)
		perror("Error al abrir file1");
	if (file_out < 0)
	{
		perror("Error al abrir file2");
		pipex(file_in, file_out, envp, (char **)argv);
		close(file_in);
		return (EXIT_FAILURE);
	}
	exit_code = pipex(file_in, file_out, envp, (char **)argv);
	close(file_in);
	close(file_out);
	return (exit_code);
}
