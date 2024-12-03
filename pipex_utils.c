/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:45:08 by root              #+#    #+#             */
/*   Updated: 2024/12/03 21:49:22 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *join_paths(const char *dir, const char *cmd)
{
    char *joined_path;
    size_t len_dir;
    size_t len_cmd;

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

char *find_command_path(char *cmd, char **envp)
{
    char *path_env;
    char *full_path;
    int i;

    if (!cmd || !*cmd || !envp)
        return (NULL);
    path_env = NULL;
    i = 0;
    while (envp[i])
    {
        if (strncmp(envp[i], "PATH=", 5) == 0)
        {
            path_env = envp[i] + 5;
            break;
        }
        i++;
    }
    if (!path_env)
        return (NULL);
    char **path_dirs = ft_split(path_env, ':');
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

void execute_command(char *cmd, char **envp)
{
    char *path;

    if (!cmd || !*cmd)
    {
        fprintf(stderr, "Comando vacío o nulo\n");
        exit(EXIT_FAILURE);
    }
    char **args = ft_split(cmd, ' ');
    if (!args || !args[0])
    {
        fprintf(stderr, "Error al dividir el comando\n");
        free_split(args);
        exit(EXIT_FAILURE);
    }
    path = find_command_path(args[0], envp);
    if (!path)
    {
        fprintf(stderr, "Comando no encontrado: %s\n", args[0]);
        free_split(args);
        exit(EXIT_FAILURE);
    }
    if (execve(path, args, envp) == -1)
    {
        perror("Error al ejecutar el comando");
        free_split(args);
        free(path);
        exit(EXIT_FAILURE);
    }
}