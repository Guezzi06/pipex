/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguezzi <aguezzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:08:59 by aguezzi           #+#    #+#             */
/*   Updated: 2023/07/03 00:49:28 by aguezzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_pipex
{
	int		*p;
	int		i;
	int		nb_pipes;
	int		fd[2];
	pid_t	*pids;
	pid_t	pid1;
	pid_t	pid2;
	char	**split1;
	char	**split2;
	char	**split;
	char	*path_env;
	char	**cmd_paths;
	char	*the_path;
}	t_pipex;

int		ft_quit(char *s);
char	*find_path(char **env);
char	*search_the_path(t_pipex *pipex, char *argv);
void	child_process(t_pipex *pipex, int argc, char **argv, char **env);
void	close_pipes_child(t_pipex *pipex, int argc, int i);
void	dup2_and_close(t_pipex *pipex, int argc, int i);
void	free_split_and_path(t_pipex *pipex);
void	create_pipes(t_pipex *pipex, int argc);
void	close_pipes_parent(t_pipex *pipex, int nb_pipes);
void	wait_childs(t_pipex *pipex, int i);
void	files_open_permission(t_pipex *pipex, char **argv, int argc);
void	ex_childs(t_pipex *pipex, int *argc, char **argv, char **env);
void	heredoc(t_pipex *pipex, char **argv, char **env);
void	heredoc_functions(t_pipex *pipex, char **argv, char **env);
void	h_execute_childs(t_pipex *pipex, char **argv);
void	first_child(t_pipex *pipex, char **argv);
void	second_child(t_pipex *pipex, char **argv);
void	specific_error(char *cmd);

#endif
