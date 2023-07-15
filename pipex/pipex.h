/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguezzi <aguezzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:30:02 by aguezzi           #+#    #+#             */
/*   Updated: 2023/07/02 23:45:46 by aguezzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "libft/ft_printf.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_pipex
{
	int		p[2];
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	**split1;
	char	**split2;
	char	*path_env;
	char	**cmd_paths;
	char	*the_path;
}	t_pipex;

int		ft_quit(char *s);
char	*find_path(char **env);
void	first_child(t_pipex *pipex, char **argv, char **env);
void	second_child(t_pipex *pipex, char **argv, char **env);
void	close_pipes_parent(t_pipex *pipex);
char	*search_the_path(t_pipex *pipex, char *argv);
void	execute_childs(t_pipex *pipex, char **argv, char **env);
void	files_open_permission(t_pipex *pipex, char **argv, int argc);
void	specific_error(char *cmd);

#endif
