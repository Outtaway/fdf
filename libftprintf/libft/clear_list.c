/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:16:05 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/04/16 12:16:15 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		clear_list(t_list *list)
{
	if (list)
	{
		if (list->next)
			clear_list(list->next);
		free(list->content);
		free(list);
	}
}
