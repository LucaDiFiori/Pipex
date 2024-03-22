/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:44:56 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/03/21 18:41:33 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*cmd_env_search(char *cmd, char **envp)
{
	int		i;
	char	**all_path;
	char	*cmd_path;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	all_path = dquote_split(envp[i] + 5, ':');
	i = 0;
	while (all_path[i])
	{
		cmd_path = ft_strjoin(ft_strjoin(all_path[i], "/"), cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			free_matrix(all_path);
			return (cmd_path);
		}
		free (cmd_path);
		i++;
	}
	free_matrix(all_path);
	return (NULL);
}

void	command(char *argv, char **envp)
{
	char	**cmd;
	char	*cmd_path;

	cmd = NULL;
	cmd_path = NULL;
	cmd = dquote_split(argv, ' ');
	if (cmd == NULL)
		quit_free("Error: Unable to split the string.\n", NULL, NULL, 1);
	cmd_path = cmd_env_search(cmd[0], envp);
	if (cmd_path == NULL)
		quit_free("Error: Command not found", NULL, cmd, 3);
	if (execve(cmd_path, cmd, envp) == -1)
		quit_free("Error executing execve\n", cmd_path, cmd, 4);
}
