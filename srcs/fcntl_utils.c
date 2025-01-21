/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcntl_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:14:25 by kporceil          #+#    #+#             */
/*   Updated: 2025/01/16 19:15:51 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	double_close(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

int	triple_close(int fd1, int fd2, int fd3, int ret)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	if (fd3 != -1)
		close(fd3);
	return (ret);
}

void	handle_input_fd_error(int *fd_1, int *fd_2, int *fd_3, int *i)
{
	close(*fd_1);
	*fd_3 = *fd_2;
	++(*i);
}
