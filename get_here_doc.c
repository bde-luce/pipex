/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:56:20 by bde-luce          #+#    #+#             */
/*   Updated: 2024/11/13 19:56:20 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	line_cmp_lim(char *line, char **argv)
{
	if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
	{
		if (line[ft_strlen(argv[2])] == '\n')
			return (1);
	}
	return (0);
}

static void	no_eof_error(char **argv)
{
	write(2, "Warning: here-document delimited by end-of-file (wanted `", 57);
	write(2, argv[2], sizeof(char) * ft_strlen(argv[2]));
	write(2, "')\n", 3);
}

void	get_here_doc(int *fd_pipe1, char **argv)
{
	char	*line;

	line = get_next_line(0);
	while (line && line_cmp_lim(line, argv) == 0)
	{
		write(fd_pipe1[1], line, sizeof(char) * ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(line);
	if (line == NULL)
		no_eof_error(argv);
	close(fd_pipe1[0]);
	close(fd_pipe1[1]);
	exit(0);
}
