/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 08:30:54 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/20 17:14:33 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_pipes(t_arg *arg)
{
	int	i;

	i = 0;
	while (arg)
	{
		if (arg->token == TOKEN_PIPE)
			i++;
		arg = arg->next;
	}
	if (i == 0)
		return (-1);
	return (i);
}

int	ft_try(t_arg *arg, t_env *env, int pipes, int std[2])
{
	char	**env_tab;
	int		i;

	i = -1;
	env_tab = ft_env_to_char(env);
	while (arg)
	{
		if (++i < pipes)
			ft_piped_child(arg, env_tab, std);
		else
			ft_child(arg, env_tab, std);
		arg = ft_get_next_pipe(arg);
	}
	env_tab = ft_magic_malloc(FREE, 0, env_tab);
	while (pipes-- > 0)
		waitpid(0, NULL, 0);
	return (0);
}

int	ft_piped_child(t_arg *arg, char **env_tab, int std[2])
{
	char	**paths;
	pid_t	child;
	int		fds[2];

	if (pipe(fds) == -1)
		return (1);
	child = fork();
	if (child == -1)
		return (1);
	if (child == 0)
	{
		dup2(fds[1], STDOUT_FILENO);
		paths = ft_get_path(env_tab);
		ft_executor(arg, paths, env_tab, std);
		ft_close_child(fds, std);
		ft_magic_malloc(FLUSH, 0, NULL);
	}
	else
	{
		dup2(fds[0], STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		close(fds[0]);
	}
	return (0);
}

int	ft_child(t_arg *arg, char **env_tab, int std[2])
{
	char	**paths;
	pid_t	child;
	int		fds[2];

	if (pipe(fds) == -1)
		return (1);
	child = fork();
	if (child == -1)
		return (1);
	if (child == 0)
	{
		paths = ft_get_path(env_tab);
		ft_executor(arg, paths, env_tab, std);
		ft_close_child(fds, std);
		ft_magic_malloc(FLUSH, 0, NULL);
	}
	close(fds[1]);
	close(fds[0]);
	dup2(std[1], STDOUT_FILENO);
	dup2(std[0], STDIN_FILENO);
	waitpid(0, NULL, 0);
	return (0);
}

int	ft_executor(t_arg *arg, char **paths, char **env_tab, int std[2])
{
	char	*cmd;
	t_env	*env;
	char	**args_tab;

	args_tab = ft_list_to_char(arg);
	env = ft_env_to_list(env_tab);
	if (ft_builtin_parser(&env, arg, std) == 42)
	{
		if (ft_check_cmd(args_tab[0]) != 0)
			return (-1);
		if (execve(args_tab[0], args_tab, env_tab) == -1 && env_tab)
		{
			cmd = ft_get_cmd(args_tab[0], paths);
			if (cmd == NULL || execve(cmd, args_tab, env_tab) == -1)
			{
				ft_eprintf("%s: %s\n", args_tab[0], NOT_FOUND);
				cmd = ft_magic_malloc(FREE, 0, cmd);
				args_tab = ft_magic_malloc(FREE, 0, args_tab);
				return (-1);
			}
		}
	}
	return (-1);
}