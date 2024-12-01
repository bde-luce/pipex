/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:47:36 by bde-luce          #+#    #+#             */
/*   Updated: 2024/11/12 23:47:36 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_1sthalf(int *fd_pipe, char **argv, char **envp)
{
	int fd_in;

	fd_in = fd_infile(argv);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	exec_command(argv[2], envp);
}

void	pipe_loop(int *fd_pipe, int *fd_next_pipe, char *argument, char **envp)
{
	int		pid_loop;

	create_pipe(fd_next_pipe);
	pid_loop = fork();
	if (pid_loop == -1)
		error_fork();
	if (pid_loop == 0)
	{
		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		dup2(fd_next_pipe[1], STDOUT_FILENO);
		close(fd_next_pipe[0]);
		close(fd_next_pipe[1]);
		exec_command(argument, envp);
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
}

void	exec_mid(int (*fd_pipe)[2], int argc, char **argv, char **envp)
{
	int	i;
	int	fd_next_pipe[2];

	i = 3;
	while (i < argc - 2)
	{
		pipe_loop(*fd_pipe, fd_next_pipe, argv[i++], envp);
		(*fd_pipe)[0] = fd_next_pipe[0];
		(*fd_pipe)[1] = fd_next_pipe[1];
	}
	wait(NULL);
}

void	exec_2ndhalf(int *fd_pipe, int argc, char **argv, char **envp)
{
	int fd_out;

	fd_out = fd_outfile(argc, argv);
	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	exec_command(argv[argc -2], envp);
}

void	make_pipe(int argc, char **argv, char **envp)
{
	int	fd_pipe[2];
	int	pid1;
	int	pid2;

	create_pipe(fd_pipe);
	pid1 = fork();
	if (pid1 == -1)
		error_fork();
	if (pid1 == 0)
		exec_1sthalf(fd_pipe, argv, envp);
	if (argc > 5)
		exec_mid(&fd_pipe, argc, argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		error_fork();
	if (pid2 == 0)
		exec_2ndhalf(fd_pipe, argc, argv, envp);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
