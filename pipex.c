/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:03:48 by bde-luce          #+#    #+#             */
/*   Updated: 2024/11/02 20:03:48 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (ft_strncmp(argv[1], "here_doc", sizeof(char) * 8) == 0)
	{
		if (argc < 6)
			error_arg();
		else
		{
			make_here_doc(argc, argv, envp);
			return (0);
		}
	}
	else if (argc < 5)
		error_arg();
	else
	{
		make_pipe(argc, argv, envp);
		return (0);
	}
}
