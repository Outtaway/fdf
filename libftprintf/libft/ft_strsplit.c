/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 14:46:30 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/01/11 11:15:22 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	words(char const *s, char c, int all)
{
	size_t i;
	size_t words;

	words = 0;
	i = 0;
	while (1)
	{
		while ((s[i] == c && !all) || (all && ftblank(s[i])))
			++i;
		if (s[i] == '\0')
			break ;
		words++;
		while (((s[i] != c && !all) ||
								(all && !ftblank(s[i]))) && s[i] != '\0')
			++i;
		if (s[i] == '\0')
			break ;
	}
	return (words);
}

char			**ft_strsplit(char const *s, char c, int all)
{
	char	**arr;
	int		i;
	size_t	temp;
	size_t	j;

	if (!s)
		return (NULL);
	if (!(arr = (char **)malloc((words(s, c, all) + 1) * sizeof(char *))))
		return (NULL);
	j = 0;
	i = -1;
	while (++i >= 0)
	{
		while (((s[j] == c && !all) || (all && ftblank(s[j]))) && s[j] != '\0')
			++j;
		if (s[j] == '\0')
			break ;
		temp = j;
		while (((s[j] != c && !all) || (all && !ftblank(s[j]))) && s[j] != '\0')
			++j;
		arr[i] = ft_strnew(j - temp);
		arr[i] = ft_strncpy(arr[i], s + temp, j - temp);
	}
	arr[i] = (NULL);
	return (arr);
}
