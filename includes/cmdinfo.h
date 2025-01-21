/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdinfo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:18:10 by kporceil          #+#    #+#             */
/*   Updated: 2025/01/14 15:43:12 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDINFO_H
# define CMDINFO_H

typedef struct s_cmdinfo
{
	char	**path;
	char	**cmd;
	char	**envp;
	int		input_fd;
	int		output_fd;
}				t_cmdinfo;

#endif
