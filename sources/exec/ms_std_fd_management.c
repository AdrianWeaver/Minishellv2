/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_std_fd_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:25:56 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/25 13:11:13 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_child(int fds[2], int std[2])
{
	close(fds[1]);
	close(fds[0]);
	close(std[1]);
	close(std[0]);
	close(0);
	close(1);
}

void	ft_close_parent(int std[2])
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
}
