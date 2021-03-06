/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isblunk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 14:54:35 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/01/11 11:15:36 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ftblank(char c)
{
	return (c == '\n' || c == ' ' || c == '\t'
		|| c == '\v' || c == '\b') ? 1 : 0;
}
