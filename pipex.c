/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:55:35 by rmakende          #+#    #+#             */
/*   Updated: 2024/10/31 21:00:08 by rmakende         ###   ########.fr       */
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

int main(int argc, char const *argv[])  //Dani: Necesitas buscar el comando (si no te dan una ruta) en el PATH, que viene por env! Pero recuerda que, a lo mejor, no hay PATH...
{
    int infile_fd, outfile_fd;
    int pipefd[2];
    pid_t pid1, pid2;

//  if (argc == 5)  //Dani: argc siempre va a ser distinto de 0, necesitas capar que haya 4 y solo 4 argumentos (5, si contamos el nombre del ejecutable).
    if (argc != 0)  // Esperamos 4 argumentos (infile, grep, wc, outfile)
    {
        // Abre infile en modo lectura
        infile_fd = open(argv[1], O_RDONLY | O_CREAT, 0666);//Dani: Permisos para qué? Por qué creas el archivo infile? Qué hace el comando que estás imitando?
        if (infile_fd == -1)
        {
            perror("Error al abrir infile");//Dani: Este error no se gestiona aquí, se gestiona dentro de los hijos, prueba "< infile hfdsdd | sleep 2 > outfile"
            return (-1);
        }

        // Abre outfile en modo escritura
        outfile_fd = open(argv[4], O_WRONLY | O_CREAT, 0666);//Dani: Permisos incorrectos, Bash los crea con 0644
        if (outfile_fd == -1) {
            perror("Error al abrir outfile");//Dani: Este error no se gestiona aquí, se gestiona dentro de los hijos, prueba "< infile sleep 3 | sdfsd > outfile"
            close(infile_fd);
            return (-1);
        }

        // Crea una pipe
        if (pipe(pipefd) == -1) {
            perror("Error al crear la pipe");
            close(infile_fd);
            close(outfile_fd);
            return (-1);
        }

        // Proceso para ejecutar el comando `grep`
        pid1 = fork();
        if (pid1 == -1) {
            perror("Error en fork para grep");
            close(infile_fd);   //Dani: Y la pipe no la cierras?
            close(outfile_fd);
            return (-1);
        }

        if (pid1 == 0)  // Proceso hijo para grep
        {
            // Redirige la entrada de `grep` a infile
            dup2(infile_fd, STDIN_FILENO);
            // Cierra el extremo de escritura de la pipe
            close(pipefd[0]);
            // Redirige la salida de `grep` a la pipe
            dup2(pipefd[1], STDOUT_FILENO);
            //Dani: Falta cerrar pipefd[1], infile_fd y outfile_fd
            
            // Ejecuta el comando `grep a1`
            //Dani: antes de ejecutar, es interesante notar que te dejas fds abiertos en los hijos, prueba "valgrind --trace-children=yes --track-fds=yes"
            execlp("grep", "grep", "a1", NULL); //Dani: FORBIDDEN FUNCTION!!!!!!!!!!!!!!!!!! La función que debes usar para ejecutar es "execve", que es mucho más jodida, pregúntame por ella cuando me veas xd
            perror("Error al ejecutar grep");
            exit(1); // Salir si execlp falla
        }

        // Proceso para ejecutar el comando `wc -w`
        pid2 = fork();
        if (pid2 == -1) {
            perror("Error en fork para wc");
            close(infile_fd);   //Dani: Y la pipe no la cierras?
            close(outfile_fd);
            return (-1);
        }

        if (pid2 == 0)  // Proceso hijo para wc
        {
            // Cierra el extremo de escritura de la pipe
            close(pipefd[1]);
            // Redirige la entrada de `wc` a la pipe
            dup2(pipefd[0], STDIN_FILENO);
            // Redirige la salida de `wc` al archivo outfile
            dup2(outfile_fd, STDOUT_FILENO);
            //Dani: Falta cerrar pipefd[0], infile_fd y outfile_fd

            // Ejecuta el comando `wc -w`
            //Dani: antes de ejecutar, es interesante notar que te dejas fds abiertos en los hijos, prueba "valgrind --trace-children=yes --track-fds=yes"
            execlp("wc", "wc", "-w", NULL);     //Dani: FORBIDDEN FUNCTION!!!!!!!!!!!!!!!!!! La función que debes usar para ejecutar es "execve", que es mucho más jodida, pregúntame por ella cuando me veas xd
            perror("Error al ejecutar wc");
            exit(1); // Salir si execlp falla
        }

        // Cierra los descriptores de archivos en el proceso padre
        close(infile_fd);
        close(outfile_fd);
        close(pipefd[0]);   //Dani: los fds, en el proceso padre, han de cerrarse después de cada fork! No todos juntos!
        close(pipefd[1]);

        // Espera a que terminen los procesos hijos
        wait(NULL);
        wait(NULL); //Dani: Bien hecho el esperar a todos al final!
    }
    else
    {
        perror("Número incorrecto de argumentos. Usa: ./pipex infile 'grep a1' 'wc -w' outfile");
        return (-1);
    }
    //Dani: Hay que matar a GPT por esta herejía.
    return (0);
}

