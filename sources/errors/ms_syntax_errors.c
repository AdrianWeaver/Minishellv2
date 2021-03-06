/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syntax_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:15:00 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/20 11:05:41 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_and_quit(t_arg *arg, t_arg *head)
{
	(void)head;
	if (arg == NULL)
		ft_eprintf("%s `newline\'\n", SYNTAX_ERROR);
	else if (arg->token == TOKEN_INFILE)
		ft_eprintf("%s `<\'\n", SYNTAX_ERROR);
	else if (arg->token == TOKEN_HEREDOC)
		ft_eprintf("%s `<<\'\n", SYNTAX_ERROR);
	else if (arg->token == TOKEN_OUTFILE)
		ft_eprintf("%s `>\'\n", SYNTAX_ERROR);
	else if (arg->token == TOKEN_APPENDOUT)
		ft_eprintf("%s `>>\'\n", SYNTAX_ERROR);
	else if (arg->token == TOKEN_PIPE)
		ft_eprintf("%s `|\'\n", SYNTAX_ERROR);
}

int	ft_check_double_redir(t_arg *arg)
{
	int	i;

	while (arg)
	{
		i = 0;
		if (arg->token == TOKEN_HEREDOC)
		{
			while (arg->content[i] == '<')
				i++;
			if (i > 2)
				ft_eprintf("%s `%c\'\n", SYNTAX_ERROR, arg->content[2]);
		}
		else if (arg->token == TOKEN_APPENDOUT)
		{
			while (arg->content[i] == '>')
				i++;
			if (i > 2)
				ft_eprintf("%s `%c\'\n", SYNTAX_ERROR, arg->content[2]);
		}
		if (i > 2)
			return (1);
		arg = arg->next;
	}
	return (0);
}

int	ft_check_single_redir(t_arg *arg)
{
	while (arg)
	{
		if (arg->token == TOKEN_INFILE)
		{
			if (arg->content[1] == '>')
			{
				ft_eprintf("%s `>\'\n", SYNTAX_ERROR);
				return (1);
			}
		}
		else if (arg->token == TOKEN_OUTFILE)
		{
			if (arg->content[1] == '<')
			{
				ft_eprintf("%s `<\'\n", SYNTAX_ERROR);
				return (1);
			}
		}
		arg = arg->next;
	}
	return (0);
}

int	ft_check_double_pipe(t_arg *arg, t_arg *head)
{
	if (arg->token == TOKEN_PIPE)
	{
		if (arg->next == NULL || arg->next->token == TOKEN_PIPE)
		{
			ft_clear_and_quit(arg->next, head);
			return (1);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*	ACT : check if an $ENV_VAR with name given in param exists                */
/*	ARG : string name, a pointer to a t_env struct                            */
/*	RET : 0 if $ENV_VAR exists, -1 if not                                     */
/* ************************************************************************** */

int	ft_check_env_var(char *str, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strcmp(str, temp->name) == 0)
			return (0);
		temp = temp->next;
	}
	return (-1);
}
