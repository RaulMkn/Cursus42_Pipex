/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:55:35 by rmakende          #+#    #+#             */
/*   Updated: 2024/12/03 21:57:31 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void first_forker(int pipe_fd[2], int file_in, int file_out, char **envp, char *argv[])
{
    pid_t pid1;

    pid1 = fork();
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
        execute_command(argv[2], envp);
    }
    waitpid(pid1, NULL, 0);

}

void second_forker(int pipe_fd[2], int file_in, int file_out, char **envp, char *argv[])
{
    pid_t pid2;

    pid2 = fork();
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
        execute_command(argv[3], envp);
    }
    waitpid(pid2, NULL, 0);

}
void pipex(int pipe_fd[2], int file_in, int file_out, char **envp, char *argv[])
{

    if (pipe(pipe_fd) == -1)
    {
        perror("Error al crear la tubería");
        close(file_in);
        close(file_out);
        exit(EXIT_FAILURE);
    }
    first_forker(pipe_fd, file_in, file_out, envp, argv);
    second_forker(pipe_fd, file_in, file_out, envp, argv);
    close(file_in);
	close(file_out);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

int main(int argc, char const *argv[], char **envp)
{
    int file_in;
    int file_out;
    int pipe_fd[2];
    char **arg;
    arg = (char **)argv;

    if (argc != 5)
    {
        ft_printf("Cantidad inadecuada de argumentos. Ejemplo de uso: ./pipex file1 cmd1 cmd2 file2");
        exit(EXIT_FAILURE);
    }
    file_in = open(argv[1], O_RDONLY);
    if (file_in < 0)
    {
        perror("Error al abrir file1");
        exit(EXIT_FAILURE);
    }
    file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_out < 0)
    {
        perror("Error al abrir file2");
        close(file_in);
        exit(EXIT_FAILURE);
    }
    pipex(pipe_fd, file_in, file_out, envp, arg);
}
