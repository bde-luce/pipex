/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_hd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:08:45 by bde-luce          #+#    #+#             */
/*   Updated: 2024/11/13 20:08:45 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	fd_appendfile(int argc, char **argv)
{
	int	fd_outfile;

	fd_outfile = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	return (fd_outfile);
}

void	child_proc1(int *fd_pipe1, int *fd_pipe2, char **argv, char **envp)
{
	dup2(fd_pipe1[0], STDIN_FILENO);
	close(fd_pipe1[0]);
	close(fd_pipe1[1]);
	dup2(fd_pipe2[1], STDOUT_FILENO);
	close(fd_pipe2[0]);
	close(fd_pipe2[1]);
	exec_command(argv[3], envp);
}

void	exec_mid_hd(int (*fd_pipe)[2], int argc, char **argv, char **envp)
{
	int	i;
	int	fd_next_pipe[2];

	i = 4;
	while (i < argc - 2)
	{
		pipe_loop(*fd_pipe, fd_next_pipe, argv[i++], envp);
		(*fd_pipe)[0] = fd_next_pipe[0];
		(*fd_pipe)[1] = fd_next_pipe[1];
	}
}

void	child_proc2(int *fd_pipe2, int argc, char **argv, char **envp)
{
	dup2(fd_pipe2[0], STDIN_FILENO);
	close(fd_pipe2[0]);
	close(fd_pipe2[1]);
	dup2(fd_appendfile(argc, argv), STDOUT_FILENO);
	close(fd_appendfile(argc, argv));
	exec_command(argv[argc - 2], envp);
}
