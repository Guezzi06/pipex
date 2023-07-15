/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguezzi <aguezzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:09:12 by aguezzi           #+#    #+#             */
/*   Updated: 2023/07/03 01:33:57 by aguezzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ex_childs(t_pipex *pipex, int *argc, char **argv, char **env)
{
	while (*argc > 3)
	{
		pipex->pids[pipex->i] = fork();
		if (pipex->pids[pipex->i] == -1)
			ft_quit("Miss creating fork");
		child_process(pipex, *argc, argv, env);
		pipex->i += 1;
		*argc -= 1;
	}
}

void	child_process(t_pipex *pipex, int argc, char **argv, char **env)
{
	if (pipex->pids[pipex->i] == 0)
	{
		free_split_and_path(pipex);
		pipex->split = ft_split(argv[pipex->i + 2], ' ');
		pipex->the_path = search_the_path(pipex, pipex->split[0]);
		close_pipes_child(pipex, argc, pipex->i);
		dup2_and_close(pipex, argc, pipex->i);
		execve(pipex->the_path, pipex->split, env);
	}
}

void	close_pipes_child(t_pipex *pipex, int argc, int i)
{
	int	j;

	j = 0;
	while (j < 2 * pipex->nb_pipes)
	{
		if (i == 0)
		{
			if (j != 1)
				close(pipex->p[j]);
		}
		else if (argc != 4)
		{
			if (j != i * 2 - 2 && j != i * 2 + 1)
				close(pipex->p[j]);
		}
		else
		{
			if (j != i * 2 - 2)
				close(pipex->p[j]);
		}
		j++;
	}
}

void	dup2_and_close(t_pipex *pipex, int argc, int i)
{
	if (i == 0)
	{
		if (pipex->fd[0] < 0)
			exit (1);
		dup2(pipex->fd[0], STDIN_FILENO);
		close(pipex->fd[0]);
	}
	else
	{
		close(pipex->fd[0]);
		dup2(pipex->p[i * 2 - 2], STDIN_FILENO);
		close(pipex->p[i * 2 - 2]);
	}
	if (argc != 4)
	{
		close(pipex->fd[1]);
		dup2(pipex->p[i * 2 + 1], STDOUT_FILENO);
		close(pipex->p[i * 2 + 1]);
	}
	else
	{
		dup2(pipex->fd[1], STDOUT_FILENO);
		close(pipex->fd[1]);
	}
}

void	free_split_and_path(t_pipex *pipex)
{
	int	j;

	j = 0;
	if (pipex->the_path)
		free(pipex->the_path);
	if (pipex->split)
	{
		while (pipex->split[j])
		{
			free(pipex->split[j]);
			j++;
		}
		free(pipex->split);
	}
}
