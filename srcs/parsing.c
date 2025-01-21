/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:53:18 by kporceil          #+#    #+#             */
/*   Updated: 2025/01/16 19:44:35 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "cmdinfo.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	**set_path(char **envp)
{
	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		++envp;
	if (!(*envp))
		return (ft_split("", ' '));
	*envp += 5;
	return (ft_split(*envp, ':'));
}

char	*set_cmd(t_cmdinfo *cmd_info)
{
	size_t	i;
	char	*bin_to_path;
	char	*tmp;

	i = 0;
	if (cmd_info->cmd[0])
	{
		while (cmd_info->path[i])
		{
			tmp = ft_strjoin(cmd_info->path[i], "/");
			if (!tmp)
				return (NULL);
			bin_to_path = ft_strjoin(tmp, cmd_info->cmd[0]);
			free(tmp);
			if (!bin_to_path)
				return (NULL);
			if (access(bin_to_path, X_OK) != -1)
				return (bin_to_path);
			free(bin_to_path);
			++i;
		}
		if (i != 0)
			perror(cmd_info->cmd[0]);
	}
	return (NULL);
}
