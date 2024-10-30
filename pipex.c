/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:55:35 by rmakende          #+#    #+#             */
/*   Updated: 2024/10/30 17:54:10 by rmakende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(int argc, char const *argv[])
{
    int infile_fd, outfile_fd;
    int pipefd[2];
    pid_t pid1, pid2;

    if (argc > 0)  // Esperamos 4 argumentos (infile, grep, wc, outfile)
    {
        // Abre infile en modo lectura
        infile_fd = open(argv[1], O_RDONLY | O_CREAT, 0600);
        if (infile_fd == -1) {
            perror("Error al abrir infile");
            return -1;
        }

        // Abre outfile en modo escritura
        outfile_fd = open(argv[4], O_WRONLY | O_CREAT, 0600);
        if (outfile_fd == -1) {
            perror("Error al abrir outfile");
            close(infile_fd);
            return -1;
        }

        // Crea una pipe
        if (pipe(pipefd) == -1) {
            perror("Error al crear la pipe");
            close(infile_fd);
            close(outfile_fd);
            return -1;
        }

        // Proceso para ejecutar el comando `grep`
        pid1 = fork();
        if (pid1 == -1) {
            perror("Error en fork para grep");
            close(infile_fd);
            close(outfile_fd);
            return -1;
        }

        if (pid1 == 0)  // Proceso hijo para grep
        {
            // Redirige la entrada de `grep` a infile
            dup2(infile_fd, STDIN_FILENO);
            // Cierra el extremo de escritura de la pipe
            close(pipefd[0]);
            // Redirige la salida de `grep` a la pipe
            dup2(pipefd[1], STDOUT_FILENO);

            // Ejecuta el comando `grep a1`
            execlp("grep", "grep", "a1", NULL);
            perror("Error al ejecutar grep");
            exit(1); // Salir si execlp falla
        }

        // Proceso para ejecutar el comando `wc -w`
        pid2 = fork();
        if (pid2 == -1) {
            perror("Error en fork para wc");
            close(infile_fd);
            close(outfile_fd);
            return -1;
        }

        if (pid2 == 0)  // Proceso hijo para wc
        {
            // Cierra el extremo de escritura de la pipe
            close(pipefd[1]);
            // Redirige la entrada de `wc` a la pipe
            dup2(pipefd[0], STDIN_FILENO);
            // Redirige la salida de `wc` al archivo outfile
            dup2(outfile_fd, STDOUT_FILENO);

            // Ejecuta el comando `wc -w`
            execlp("wc", "wc", "-w", NULL);
            perror("Error al ejecutar wc");
            exit(1); // Salir si execlp falla
        }

        // Cierra los descriptores de archivos en el proceso padre
        close(infile_fd);
        close(outfile_fd);
        close(pipefd[0]);
        close(pipefd[1]);

        // Espera a que terminen los procesos hijos
        wait(NULL);
        wait(NULL);
    }
    else {
        perror("Número incorrecto de argumentos. Usa: ./pipex infile 'grep a1' 'wc -w' outfile");
        return -1;
    }

    return 0;
}

