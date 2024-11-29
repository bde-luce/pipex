/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:32:26 by bde-luce          #+#    #+#             */
/*   Updated: 2024/11/04 19:32:26 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

int		fd_infile(char **argv);
int		fd_outfile(int argc, char **argv);
void	error_arg(void);
void	create_pipe(int *fd_pipe);
void	error_fork(void);
void	error_exec(char *path, char **arr_arg, char *function);
void	exec_command(char *command, char **envp);
char	*create_path(char *function, char **envp);
void	exec_1sthalf(int *fd_pipe, char **argv, char **envp);
void	pipe_loop(int *fd_pipe, int *fd_next_pipe, char *argv, char **envp);
void	exec_mid(int (*fd_pipe)[2], int argc, char **argv, char **envp);
void	exec_2ndhalf(int *fd_pipe, int argc, char **argv, char **envp);
void	make_pipe(int argc, char **argv, char **envp);
void	get_here_doc(int *fd_pipe1, char **argv);
void	child_proc1(int *fd_pipe1, int *fd_pipe2, char **argv, char **envp);
void	exec_mid_hd(int (*fd_pipe)[2], int argc, char **argv, char **envp);
void	child_proc2(int *fd_pipe2, int argc, char **argv, char **envp);
void	make_here_doc(int argc, char **argv, char **envp);

#endif