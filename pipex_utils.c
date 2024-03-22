/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:20:35 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/03/21 20:10:19 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	quit_free(const char *error, char *str, char **mat, int err_type)
{
	if (err_type == 1)
		write (2, error, s_len(error));
	else if (err_type == 2)
	{
		free(str);
		write (2, error, s_len(error));
	}
	else if (err_type == 3)
	{
		free_matrix(mat);
		write (2, error, s_len(error));
	}
	else if (err_type == 4)
	{
		free(str);
		free_matrix(mat);
		write (2, error, s_len(error));
	}
	exit (1);
}

void	free_matrix(char **mat)
{
	int	i;

	i = -1;
	while (mat[++i])
		free(mat[i]);
	free(mat);
}
