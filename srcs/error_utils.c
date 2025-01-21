/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:37:53 by kporceil          #+#    #+#             */
/*   Updated: 2025/01/16 19:39:21 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "cmdinfo.h"

int	free_double_tab(char **tab, int ret);

void	perror_free_and_exit(char *err, int exit_value, t_cmdinfo *cmd, void *p)
{
	free_double_tab(cmd->cmd, 0);
	free_double_tab(cmd->path, 0);
	free(p);
	perror(err);
	exit(exit_value);
}
