/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:25:52 by soel-mou          #+#    #+#             */
/*   Updated: 2025/04/11 22:25:53 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	err_msg(char *detail, char *str, int code)
{
	ft_putstr_fd(RED "cub3D: Error", 2);
	if (detail)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(detail, 2);
	}
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\n" RESET, 2);
	return (code);
}

int	err_msg_val(int detail, char *str, int code)
{
	ft_putstr_fd(RED "cub3D: Error: ", 2);
	ft_putnbr_fd(detail, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n" RESET, 2);
	return (code);
}
