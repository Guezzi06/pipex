/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguezzi <aguezzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 23:06:22 by aguezzi           #+#    #+#             */
/*   Updated: 2023/07/09 11:32:34 by aguezzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	heredoc(t_pipex *pipex, char **argv, char **env)
{
	char	*line;
	int		i;

	i = 0;
	pipex->p = malloc(sizeof(int) * 4);
	while (i < 4)
	{
		if (pipe(pipex->p + i) == -1)
			ft_quit("Miss creating pipes");
		i += 2;
	}
	while (1)
	{
		ft_printf("> ");
		line = get_next_line(0);
		if ((ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0
				&& ft_strlen(line) == ft_strlen(argv[2]) + 1)
			&& line[0] != '\n')
			break ;
		else
			write(pipex->p[1], line, ft_strlen(line));
	}
	free(line);
	heredoc_functions(pipex, argv, env);
	exit (0);
}

void	heredoc_functions(t_pipex *pipex, char **argv, char **env)
{
	pipex->fd[1] = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (pipex->fd[1] < 0)
		ft_quit("outfile: Permission denied");
	pipex->path_env = find_path(env);
	pipex->cmd_paths = ft_split(pipex->path_env, ':');
	h_execute_childs(pipex, argv);
	close(pipex->fd[1]);
	close(pipex->p[0]);
	close(pipex->p[1]);
	close(pipex->p[2]);
	close(pipex->p[3]);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
}

void	h_execute_childs(t_pipex *pipex, char **argv)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
		ft_quit("Error : Miss creating fork");
	if (pipex->pid1 == 0)
		first_child(pipex, argv);
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
		ft_quit("Error : Miss creating fork");
	if (pipex->pid2 == 0)
		second_child(pipex, argv);
}

void	first_child(t_pipex *pipex, char **argv)
{
	pipex->split1 = ft_split(argv[3], ' ');
	pipex->the_path = search_the_path(pipex, pipex->split1[0]);
	close(pipex->fd[1]);
	close(pipex->p[1]);
	close(pipex->p[2]);
	dup2(pipex->p[0], STDIN_FILENO);
	dup2(pipex->p[3], STDOUT_FILENO);
	close(pipex->p[0]);
	close(pipex->p[3]);
	execve(pipex->the_path, pipex->split1, NULL);
}

void	second_child(t_pipex *pipex, char **argv)
{
	pipex->split2 = ft_split(argv[4], ' ');
	pipex->the_path = search_the_path(pipex, pipex->split2[0]);
	close(pipex->p[3]);
	close(pipex->p[1]);
	close(pipex->p[0]);
	dup2(pipex->p[2], STDIN_FILENO);
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->p[2]);
	close(pipex->fd[1]);
	execve(pipex->the_path, pipex->split2, NULL);
}
