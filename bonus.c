/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:59:26 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/03/21 18:37:43 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	new_process(char *cmd, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		quit_free("Error: pipe creation failed\n", NULL, NULL, 1);
	pid = fork();
	if (pid == -1)
		quit_free("Error encountered during fork call\n", NULL, NULL, 1);
	if (pid == 0)
	{
		close(fd[0]);
		dup_and_close(fd[1], 1);
		command(cmd, envp);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
		dup_and_close(fd[0], 0);
	}
}

static void	ft_here_doc(int fd_in, char **argv)
{
	char	*input;

	write(1, "here_doc> ", 11);
	input = get_next_line(0);
	while (input && ft_strncmp(input, argv[2], s_len(argv[2])))
	{
		write(1, "here_doc> ", 11);
		write (fd_in, input, s_len(input));
		free (input);
		input = get_next_line(0);
	}
	free(input);
}

int	main(int argc, char**argv, char **envp)
{
	int	fd_file_in;
	int	fd_file_out;
	int	i;

	i = 1;
	if (argc >= 5)
	{
		fd_file_in = fd_open_input(argv);
		fd_file_out = fd_open_output(argv, argc);
		if (ft_strncmp("here_doc", argv[1], 8) == 0)
		{
			ft_here_doc(fd_file_in, argv);
			close(fd_file_in);
			fd_file_in = open (".temp", O_RDONLY, 0777);
			i = 2;
		}
		dup_and_close (fd_file_in, STDIN_FILENO);
		dup_and_close (fd_file_out, STDOUT_FILENO);
		unlink(".temp");
		while (++i < argc - 2)
			new_process(argv[i], envp);
		command(argv[i], envp);
	}
	else
		quit_free("Error: Invalid parameters\n", NULL, NULL, 1);
}
