/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eprintf_id.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:12:49 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/02 13:12:49 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

static char	*id_flag_plus_space(char *str, t_list_printf *list, int nbr,
		char **output)
{
	char	*tmp;

	if (list->flag_plus == 1 && nbr >= 0)
	{
		tmp = ft_strjoin("+", str);
		free(str);
		str = tmp;
	}
	if (list->flag_space == 1 && !(nbr < 0))
	{
		*output = ft_strjoin_free(*output, " ");
		list->ret++;
		list->width--;
	}
	return (str);
}

static char	*id_nohyphen_flag(char *str, t_list_printf *list, int nbr,
		char **output)
{
	char	*tmp;

	if (list->flag_hyphen == 0 && list->flag_zero == 0 && list->width > 1)
	{
		while (list->width > ft_strlen_int(str))
		{
			*output = ft_strjoin_free(*output, " ");
			list->width--;
		}
	}
	if (list->flag_hyphen == 0 && list->flag_zero == 1 && list->width > 1)
	{
		while (list->width > ft_strlen_int(str))
		{
			if (nbr < 0)
				tmp = ft_strjoin("-0", &str[1]);
			else if (list->flag_plus == 0)
				tmp = ft_strjoin("0", str);
			else if (list->flag_plus == 1)
				tmp = ft_strjoin("+0", &str[1]);
			free(str);
			str = tmp;
		}
	}
	return (str);
}

static char	*id_make_magic(char *str, t_list_printf *list, int nbr)
{
	char	*tmp;
	int		str_len;

	str_len = ft_strlen_int(str);
	if (nbr < 0 || (list->flag_plus == 1 && nbr >= 0))
		str_len--;
	if (list->flag_precision == 1)
	{
		while (list->precision_width > str_len)
		{
			if (nbr < 0)
				tmp = ft_strjoin("-0", &str[1]);
			else if (nbr >= 0 && list->flag_plus == 1)
				tmp = ft_strjoin("+0", &str[1]);
			else
				tmp = ft_strjoin("0", str);
			str_len++;
			free(str);
			str = tmp;
		}
	}
	return (str);
}

static char	*id_flag_precision(char *str, t_list_printf *list, int nbr)
{
	if (list->precision_width < 0)
		list->flag_precision = 0;
	if (list->flag_precision == 1 && list->precision_width == 0 && nbr == 0
		&& list->flag_plus == 0)
	{
		free(str);
		str = malloc(sizeof(*str) * 1);
		*str = 0;
		return (str);
	}
	else if (list->flag_precision == 1 && list->precision_width == 0
		&& nbr == 0 && list->flag_plus == 1)
	{
		free(str);
		str = ft_strdup("+");
		return (str);
	}
	str = id_make_magic(str, list, nbr);
	return (str);
}

void	ft_eprintf_id(int nbr, t_list_printf *list, char **output)
{
	char	*str;

	str = ft_itoa(nbr);
	str = id_flag_plus_space(str, list, nbr, output);
	str = id_flag_precision(str, list, nbr);
	str = id_nohyphen_flag(str, list, nbr, output);
	while ((list->flag_precision == 1 && list->precision_width == 0
			&& list->flag_zero == 0 && list->flag_hyphen == 0
			&& nbr == 0) && (list->width > 0) && list->flag_plus == 0)
	{
		*output = ft_strjoin_free(*output, " ");
		list->ret++;
		list->width--;
	}
	*output = ft_strjoin_free(*output, str);
	list->ret += ft_strlen_int(str);
	list->width -= ft_strlen_int(str);
	ft_eflag_hyphen(list, output);
	list->i++;
	free(str);
}
