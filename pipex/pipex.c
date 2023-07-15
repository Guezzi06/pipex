/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguezzi <aguezzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:26:11 by aguezzi           #+#    #+#             */
/*   Updated: 2023/07/03 00:42:25 by aguezzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
		ft_quit("Error : Argument number invalid");
	files_open_permission(&pipex, argv, argc);
	if (pipe(pipex.p) == -1)
		ft_quit("Error : Miss creating pipe");
	pipex.path_env = find_path(env);
	pipex.cmd_paths = ft_split(pipex.path_env, ':');
	execute_childs(&pipex, argv, env);
	close_pipes_parent(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}

void	files_open_permission(t_pipex *pipex, char **argv, int argc)
{
	pipex->fd[0] = open(argv[1], O_RDONLY, 0644);
	if (pipex->fd[0] < 0)
	{
		if (errno == ENOENT)
			ft_printf("%s: No such file or directory\n", argv[1]);
		else if (errno == EACCES)
			ft_printf("%s: Permission denied\n", argv[1]);
		else
			perror("Erreur lors de l'ouverture du fichier\n");
	}
	pipex->fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd[1] < 0)
	{
		if (errno == ENOENT)
			ft_printf("%s: No such file or directory\n", argv[argc - 1]);
		else if (errno == EACCES)
			ft_printf("%s: Permission denied\n", argv[argc - 1]);
		else
			perror("Erreur lors de l'ouverture du fichier\n");
		exit (1);
	}
}

int	ft_quit(char *s)
{
	ft_printf("%s\n", s);
	exit (1);
}
