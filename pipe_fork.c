/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:58:23 by bde-luce          #+#    #+#             */
/*   Updated: 2024/11/05 23:58:23 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fd_infile(char **argv)
{
	int	fd_infile;

	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
	{
		perror("Error opening infile");
		exit(1);
	}
	return (fd_infile);
}

int	fd_outfile(int argc, char **argv)
{
	int	fd_outfile;

	fd_outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_outfile == -1)
	{
		perror("Error opening outfile");
		exit(1);
	}
	return (fd_outfile);
}

void	error_arg(void)
{
	write(2, "Invalid number of arguments\n", 28);
	exit(1);
}

void	create_pipe(int *fd_pipe)
{
	if (pipe(fd_pipe) == -1)
	{
		perror("Error creating pipe");
		exit(1);
	}
}

void	error_fork(void)
{
	perror("Error fork");
	exit(1);
}
