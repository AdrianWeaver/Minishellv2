/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@42.fr>                     +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:50:34 by aweaver           #+#    #+#             */
/*   Updated: 2022/06/27 19:10:10 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5000
# endif

# ifndef GNL_FLUSH
#  define GNL_FLUSH -1
# endif

# ifndef GET_NEXT_LINE
#  define GET_NEXT_LINE

char	*get_next_line(int fd);

# endif
#endif
