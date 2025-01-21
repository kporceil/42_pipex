/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:32:09 by kporceil          #+#    #+#             */
/*   Updated: 2025/01/16 19:37:19 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/includes/libft.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc == 5)
		return (pipex(argc, argv, envp));
	ft_putstr_fd("Wrong args.\nUsage : ./pipex infile cmd1 cmd2 outfile\n", 2);
	return (1);
}
