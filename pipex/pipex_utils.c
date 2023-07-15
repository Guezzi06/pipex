/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguezzi <aguezzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:07:36 by aguezzi           #+#    #+#             */
/*   Updated: 2023/07/02 23:45:38 by aguezzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			return (env[i] + 5);
		i++;
	}
	ft_quit("Error : variable PATH not found");
	return (0);
}

char	*search_the_path(t_pipex *pipex, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path_cmd;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (pipex->cmd_paths[i])
	{
		tmp = ft_strjoin(pipex->cmd_paths[i], "/");
		path_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path_cmd, 0) == 0)
		{
			if (access(path_cmd, X_OK) == 0)
				return (path_cmd);
			ft_printf("%s: Permission denied\n", path_cmd);
			free(path_cmd);
			exit (1);
		}
		free(path_cmd);
		i++;
	}
	specific_error(cmd);
	return (0);
}

void	specific_error(char *cmd)
{
	if (ft_strchr(cmd, '/') == 0)
	{
		ft_printf("%s: ", cmd);
		ft_quit("No such file or directory");
	}
	else
	{
		ft_printf("%s: ", cmd);
		ft_quit("command not found");
	}
}

void	close_pipes_parent(t_pipex *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	close(pipex->p[0]);
	close(pipex->p[1]);
}
