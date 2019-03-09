/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 19:47:57 by kpshenyc          #+#    #+#             */
/*   Updated: 2018/10/26 19:47:59 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	if (n <= 9 && n >= -9)
	{
		(n < 0) ? ft_putchar('-') : 0;
		(n < 0) ? ft_putchar(-n % 10 + 48) : ft_putchar(n % 10 + 48);
	}
	else
	{
		ft_putnbr(n / 10);
		(n < 0) ? ft_putchar((-n - 10) % 10 + 48)
		: ft_putchar((n - 10) % 10 + 48);
	}
}