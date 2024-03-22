/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:37:06 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/03/21 19:19:46 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_p(char **argv, char **envp, int *fd)
{
	int	fd_file_in;

	fd_file_in = open(argv[1], O_RDONLY, 0777);
	if (fd_file_in == -1)
		quit_free("Error: Unable to open input file\n", NULL, NULL, 1);
	close(fd[0]);
	dup2(fd_file_in, 0);
	close(fd_file_in);
	dup2(fd[1], 1);
	close(fd[1]);
	command(argv[2], envp);
}

static void	parent_p(char **argv, char **envp, int *fd)
{
	int	fd_file_out;

	fd_file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_file_out == -1)
		quit_free("Error: Unable to open output file\n", NULL, NULL, 1);
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	dup2(fd_file_out, 1);
	close(fd_file_out);
	command(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			quit_free("Error: pipe creation failed\n", NULL, NULL, 1);
		pid = fork();
		if (pid == -1)
			quit_free("Error encountered during fork call\n", NULL, NULL, 1);
		if (pid == 0)
			child_p(argv, envp, fd);
		else
		{
			waitpid(pid, NULL, 0);
			parent_p(argv, envp, fd);
		}
	}
	else
		quit_free("Error: Ivalid parameters\n", NULL, NULL, 1);
}
