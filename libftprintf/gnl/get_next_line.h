/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 10:19:12 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/06/13 17:59:39 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# include "../includes/ft_printf.h"
# define BUFF_SIZE 16
# define GNL1 { temp = (str) ? str : NULL; str = NULL; }
# define GNL2 { str = ft_strsub(slash + 1, 0, ft_strlen(slash + 1)); end = 1; }
# define GNL3 { GNL2; break ; }

int		get_next_line(const int fd, char **line, const int buff_size);

#endif
