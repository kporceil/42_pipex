/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:42:48 by kporceil          #+#    #+#             */
/*   Updated: 2025/01/19 17:55:16 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "../../libft/includes/libft.h"
#include "get_next_line.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#ifndef TMP_FILE
# define TMP_FILE ".here_doc"
#endif

static int	write_here_doc(int fd, char *limiter, size_t lim_size)
{
	char	*line;

	ft_putstr_fd(">", 1);
	line = get_next_line(0);
	while (line && !(ft_strncmp(limiter, line, lim_size) == 0
			&& line[lim_size] == '\n'))
	{
		ft_putstr_fd(line, fd);
		ft_putstr_fd(">", 1);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	return (0);
}

static int	create_file(char *limiter)
{
	int		fd;
	size_t	limiter_size;

	if (!(limiter[0]))
	{
		ft_putstr_fd("Invalid limiter", 2);
		return (-1);
	}
	limiter_size = ft_strlen(limiter);
	fd = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(TMP_FILE);
		return (-2);
	}
	if (write_here_doc(fd, limiter, limiter_size) != 0)
	{
		close(fd);
		return (-3);
	}
	close(fd);
	return (0);
}

int	handle_here_doc(int argc, char **argv)
{
	int	i;

	i = 3;
	if (create_file(argv[2]) != 0)
		return (-1);
	while (i < argc)
	{
		argv[i - 1] = argv[i];
		++i;
	}
	argv[1] = TMP_FILE;
	--argc;
	return (argc);
}

void	delete_here_doc(void)
{
	unlink(TMP_FILE);
}
