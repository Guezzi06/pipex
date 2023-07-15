/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguezzi <aguezzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:09:07 by aguezzi           #+#    #+#             */
/*   Updated: 2023/07/03 00:53:55 by aguezzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc < 4)
		ft_quit("Error : Argument number invalid");
	if (ft_strcmp("here_doc", argv[1]) == 0)
	{
		if (argc != 6)
			ft_quit("Error : Argument number invalid for this heredoc");
		heredoc(&pipex, argv, env);
	}
	files_open_permission(&pipex, argv, argc);
	create_pipes(&pipex, argc);
	pipex.path_env = find_path(env);
	pipex.cmd_paths = ft_split(pipex.path_env, ':');
	pipex.pids = malloc(sizeof(int) * (argc - 3));
	ex_childs(&pipex, &argc, argv, env);
	close_pipes_parent(&pipex, (argc + pipex.i - 3));
	wait_childs(&pipex, pipex.i);
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

void	wait_childs(t_pipex *pipex, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		waitpid(pipex->pids[j], NULL, 0);
		j++;
	}
}

int	ft_quit(char *s)
{
	ft_printf("%s\n", s);
	exit (1);
}
