/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:56:34 by bde-luce          #+#    #+#             */
/*   Updated: 2024/11/13 19:56:34 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	make_here_doc1(int *fd_pipe1, char **argv)
{
	int	pid1;

	create_pipe(fd_pipe1);
	pid1 = fork();
	if (pid1 == -1)
		error_fork();
	if (pid1 == 0)
		get_here_doc(fd_pipe1, argv);
	waitpid(pid1, NULL, 0);
}

static void	make_here_doc2(int *fd_pipe1, int argc, char **argv, char **envp)
{
	int	fd_pipe2[2];
	int	pid2;
	int	pid3;

	create_pipe(fd_pipe2);
	pid2 = fork();
	if (pid2 == -1)
		error_fork();
	if (pid2 == 0)
		child_proc1(fd_pipe1, fd_pipe2, argv, envp);
	close(fd_pipe1[0]);
	close(fd_pipe1[1]);
	if (argc > 6)
		exec_mid_hd(&fd_pipe2, argc, argv, envp);
	pid3 = fork();
	if (pid3 == -1)
		error_fork();
	if (pid3 == 0)
		child_proc2(fd_pipe2, argc, argv, envp);
	close(fd_pipe2[0]);
	close(fd_pipe2[1]);
	waitpid(pid2, NULL, 0);
	waitpid(pid3, NULL, 0);
}

void	make_here_doc(int argc, char **argv, char **envp)
{
	int	fd_pipe1[2];

	make_here_doc1(fd_pipe1, argv);
	make_here_doc2(fd_pipe1, argc, argv, envp);
}
