/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguezzi <aguezzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:34:28 by aguezzi           #+#    #+#             */
/*   Updated: 2023/07/03 01:35:48 by aguezzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_childs(t_pipex *pipex, char **argv, char **env)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
		ft_quit("Error : Miss creating fork");
	if (pipex->pid1 == 0)
		first_child(pipex, argv, env);
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
		ft_quit("Error : Miss creating fork");
	if (pipex->pid2 == 0)
		second_child(pipex, argv, env);
}

void	first_child(t_pipex *pipex, char **argv, char **env)
{
	if (pipex->fd[0] < 0)
		exit (1);
	pipex->split1 = ft_split(argv[2], ' ');
	pipex->the_path = search_the_path(pipex, pipex->split1[0]);
	close(pipex->p[0]);
	close(pipex->fd[1]);
	dup2(pipex->fd[0], STDIN_FILENO);
	dup2(pipex->p[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	close(pipex->p[1]);
	execve(pipex->the_path, pipex->split1, env);
}

void	second_child(t_pipex *pipex, char **argv, char **env)
{
	pipex->split2 = ft_split(argv[3], ' ');
	pipex->the_path = search_the_path(pipex, pipex->split2[0]);
	close(pipex->p[1]);
	close(pipex->fd[0]);
	dup2(pipex->p[0], STDIN_FILENO);
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->p[0]);
	close(pipex->fd[1]);
	execve(pipex->the_path, pipex->split2, env);
}
