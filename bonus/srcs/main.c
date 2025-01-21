/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:32:09 by kporceil          #+#    #+#             */
/*   Updated: 2025/01/19 17:55:38 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "heredoc.h"
#include "../../libft/includes/libft.h"

int	main(int argc, char **argv, char **envp)
{
	int	ret;

	if (argc < 5)
	{
		ft_putstr_fd("Wrong args.\nUsage : ./pipex infile cmd1 cmd2 outfile\n",
			2);
		return (1);
	}
	if (ft_strncmp(argv[1], "here_doc\0", 9) == 0)
	{
		argc = handle_here_doc(argc, argv);
		if (argc == -1)
			return (2);
		ret = pipex(argc, argv, envp, 1);
		delete_here_doc();
		return (ret);
	}
	else
		ret = pipex(argc, argv, envp, 0);
	return (ret);
}
