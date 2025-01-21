/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:46:30 by kporceil          #+#    #+#             */
/*   Updated: 2025/01/19 17:26:32 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/libft.h"
#include "cmdinfo.h"
#include "parsing.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	double_close(int fd1, int fd2);
void	perror_free_and_exit(char *err, int ex_value, t_cmdinfo *cmd, void *p);
int		free_double_tab(char **tab, int ret);
int		triple_close(int fd1, int fd2, int fd3, int ret);
void	handle_input_fd_error(int *fd_1, int *fd_2, int *fd_3, int *i);

static int	exec_cmd(t_cmdinfo *cmd_info, int i_fd, int o_fd, int to_close_fd)
{
	char	*cmd;
	pid_t	pid;

	cmd = set_cmd(cmd_info);
	if (!cmd)
		return (double_close(i_fd, o_fd), -1);
	pid = fork();
	if (pid == -1)
		return (-2);
	if (pid == 0)
	{
		if (dup2(i_fd, STDIN_FILENO) == -1 || dup2(o_fd, STDOUT_FILENO) == -1)
			perror_free_and_exit("dup2", 1, cmd_info, cmd);
		triple_close(i_fd, o_fd, to_close_fd, 0);
		if (execve(cmd, cmd_info->cmd, cmd_info->envp) == -1)
			perror_free_and_exit("execve", 2, cmd_info, cmd);
		exit(0);
	}
	else
	{
		double_close(i_fd, o_fd);
		free(cmd);
		return (0);
	}
}

static int	exec_last_cmd(char *cmd, char *ofile, int i_fd, t_cmdinfo *cmd_info)
{
	int	output_fd;
	int	status;

	if (cmd_info->append == 0)
		output_fd = open(ofile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		output_fd = open(ofile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (output_fd == -1)
		return (triple_close(i_fd, -1, -1, -3));
	cmd_info->cmd = ft_split(cmd, ' ');
	if (!cmd_info->cmd)
		return (double_close(output_fd, i_fd), -2);
	status = exec_cmd(cmd_info, i_fd, output_fd, -1);
	double_close(i_fd, output_fd);
	if (status != 0)
		return (free_double_tab(cmd_info->cmd, -1));
	return (free_double_tab(cmd_info->cmd, 0));
}

static int	run_cmds(int argc, char **argv, t_cmdinfo *cmd_info)
{
	int	i;
	int	input_fd;
	int	pipefd[2];

	i = 2;
	input_fd = open(argv[1], O_RDONLY);
	while (i < argc - 2)
	{
		if (pipe(pipefd) == -1)
			return (-2);
		if (input_fd == -1)
		{
			handle_input_fd_error(pipefd + 1, pipefd, &input_fd, &i);
			continue ;
		}
		cmd_info->cmd = ft_split(argv[i], ' ');
		if (!cmd_info->cmd)
			return (-3);
		exec_cmd(cmd_info, input_fd, pipefd[1], pipefd[0]);
		input_fd = pipefd[0];
		free_double_tab(cmd_info->cmd, 0);
		++i;
	}
	exec_last_cmd(argv[argc - 2], argv[argc - 1], input_fd, cmd_info);
	return (0);
}

static int	wait_childs(void)
{
	int	status;

	status = 0;
	while (1)
	{
		if (wait(&status) == -1)
			break ;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}

int	pipex(int argc, char **argv, char **envp, int append)
{
	t_cmdinfo	cmd_info;

	cmd_info.envp = envp;
	cmd_info.path = set_path(envp);
	cmd_info.append = 0;
	if (append == 1)
		cmd_info.append = 1;
	if (!cmd_info.path)
		return (-1);
	run_cmds(argc, argv, &cmd_info);
	(void)free_double_tab(cmd_info.path, 0);
	return (wait_childs());
}
