/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:09:14 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/03/21 19:53:54 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "get_next_line/get_next_line.h"

int			quit_free(const char *error, char *str, char **mat, int err_type);
void		free_matrix(char **mat);
char		*ft_substr(char const *s, int start, int len);
const char	*ft_strchar(const char *str, const char c);
char		*ft_strjoin(char const *s1, char const *s2);
char		**dquote_split(char const *str, char c);
char		*ft_strdup(const char *src);
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		*ft_strnstr(const char *source, const char *to_find, size_t len);
void		ft_putstr_fd(char *s, int fd);
int			s_len(const char *s);
void		command(char *argv, char **envp);
int			skip_quote(const char *str, int i, int flag, int *end_word);
int			count_quote(char const *str);
int			fd_open_input(char **argv);
int			fd_open_output(char **argv, int argc);
void		dup_and_close(int fd_to_dup, int fd_needed);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
