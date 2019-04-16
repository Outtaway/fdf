# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 14:46:20 by kpshenyc          #+#    #+#              #
#    Updated: 2019/03/07 14:16:00 by kpshenyc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

OK_COLOR = \x1b[32;01m
WARN_COLOR  = \033[0;33m
ERROR_COLOR = \x1b[31;01m
NO_COLOR  = \033[m

NAME = libftprintf.a

LIBFT = libft/libft.a

OS=$(shell uname)
ifeq ($(OS), Linux)
FLAGS=
else
FLAGS=-Wextra -Wall -Werror
endif

SRC = srcs/additional_func.c\
	srcs/ft_printf.c\
	srcs/handle_addr.c\
	srcs/handle_arr.c\
	srcs/handle_binary.c\
	srcs/handle_char.c\
	srcs/handle_decimal.c\
	srcs/handle_float.c\
	srcs/handle_hex.c\
	srcs/handle_octal.c\
	srcs/handle_procent.c\
	srcs/handle_str.c\
	srcs/handle_unsigned.c\
	srcs/parse.c\
	srcs/print_seq.c\
	libft/ft_128itoa_base.c\
	libft/ft_128value_width.c\
	libft/ft_atoi.c\
	libft/ft_bzero.c\
	libft/ft_isalnum.c\
	libft/ft_isalpha.c\
	libft/ft_isascii.c\
	libft/ft_isblunk.c\
	libft/ft_isdigit.c\
	libft/ft_isprint.c\
	libft/ft_itoa.c\
	libft/ft_lstadd.c\
	libft/ft_lstdel.c\
	libft/ft_lstdelone.c\
	libft/ft_lstiter.c\
	libft/ft_lstmap.c\
	libft/ft_lstnew.c\
	libft/ft_memalloc.c\
	libft/ft_memccpy.c\
	libft/ft_memchr.c\
	libft/ft_memcmp.c\
	libft/ft_memcpy.c\
	libft/ft_memdel.c\
	libft/ft_memmove.c\
	libft/ft_memset.c\
	libft/ft_putchar.c\
	libft/ft_putchar_fd.c\
	libft/ft_putendl.c\
	libft/ft_putendl_fd.c\
	libft/ft_putlong.c\
	libft/ft_putnbr.c\
	libft/ft_putnbr_fd.c\
	libft/ft_putstr.c\
	libft/ft_putstr_fd.c\
	libft/ft_putstrn.c\
	libft/ft_putulong.c\
	libft/ft_stack_clear.c\
	libft/ft_stack_pop.c\
	libft/ft_stack_push.c\
	libft/ft_strcat.c\
	libft/ft_strchr.c\
	libft/ft_strclr.c\
	libft/ft_strcmp.c\
	libft/ft_strcpy.c\
	libft/ft_strdel.c\
	libft/ft_strdup.c\
	libft/ft_strequ.c\
	libft/ft_striter.c\
	libft/ft_striteri.c\
	libft/ft_strjoin.c\
	libft/ft_strlcat.c\
	libft/ft_strlen.c\
	libft/ft_strmap.c\
	libft/ft_strmapi.c\
	libft/ft_strncat.c\
	libft/ft_strncmp.c\
	libft/ft_strncpy.c\
	libft/ft_strnequ.c\
	libft/ft_strnew.c\
	libft/ft_strnstr.c\
	libft/ft_strrchr.c\
	libft/ft_strsplit.c\
	libft/ft_strstr.c\
	libft/ft_strsub.c\
	libft/ft_strtrim.c\
	libft/ft_swap_int.c\
	libft/ft_tolower.c\
	libft/ft_toupper.c\
	libft/ft_uitoa_base.c\
	libft/ft_value_width.c\
	libft/free_array.c\
	libft/ft_lstsize.c\
	libft/clear_list.c\

GNL=gnl/get_next_line.c

SRO = additional_func.o\
	ft_printf.o\
	handle_addr.o\
	handle_arr.o\
	handle_binary.o\
	handle_char.o\
	handle_decimal.o\
	handle_float.o\
	handle_hex.o\
	handle_octal.o\
	handle_procent.o\
	handle_str.o\
	handle_unsigned.o\
	parse.o\
	print_seq.o\
	ft_128itoa_base.o\
	ft_128value_width.o\
	ft_atoi.o\
	ft_bzero.o\
	ft_isalnum.o\
	ft_isalpha.o\
	ft_isascii.o\
	ft_isblunk.o\
	ft_isdigit.o\
	ft_isprint.o\
	ft_itoa.o\
	ft_lstadd.o\
	ft_lstdel.o\
	ft_lstdelone.o\
	ft_lstiter.o\
	ft_lstmap.o\
	ft_lstnew.o\
	ft_memalloc.o\
	ft_memccpy.o\
	ft_memchr.o\
	ft_memcmp.o\
	ft_memcpy.o\
	ft_memdel.o\
	ft_memmove.o\
	ft_memset.o\
	ft_putchar.o\
	ft_putchar_fd.o\
	ft_putendl.o\
	ft_putendl_fd.o\
	ft_putlong.o\
	ft_putnbr.o\
	ft_putnbr_fd.o\
	ft_putstr.o\
	ft_putstr_fd.o\
	ft_putstrn.o\
	ft_putulong.o\
	ft_stack_clear.o\
	ft_stack_pop.o\
	ft_stack_push.o\
	ft_strcat.o\
	ft_strchr.o\
	ft_strclr.o\
	ft_strcmp.o\
	ft_strcpy.o\
	ft_strdel.o\
	ft_strdup.o\
	ft_strequ.o\
	ft_striter.o\
	ft_striteri.o\
	ft_strjoin.o\
	ft_strlcat.o\
	ft_strlen.o\
	ft_strmap.o\
	ft_strmapi.o\
	ft_strncat.o\
	ft_strncmp.o\
	ft_strncpy.o\
	ft_strnequ.o\
	ft_strnew.o\
	ft_strnstr.o\
	ft_strrchr.o\
	ft_strsplit.o\
	ft_strstr.o\
	ft_strsub.o\
	ft_strtrim.o\
	ft_swap_int.o\
	ft_tolower.o\
	ft_toupper.o\
	ft_uitoa_base.o\
	ft_value_width.o\
	free_array.o\
	get_next_line.o\
	ft_lstsize.o\
	clear_list.o\

all: $(NAME)

$(NAME):
	@echo "$(WARN_COLOR)-----------------------------------------------------------$(NO_COLOR)"
	@gcc -c $(FLAGS) $(SRC) $(GNL)
	@echo "\tCompiling srcs-files $(OK_COLOR)                [done]$(NO_COLOR)"
	@ar rc $(NAME) $(SRO)
	@mv $(SRO) obj/
	@echo "\tCreating libftprintf static library $(OK_COLOR) [done]"
	@echo "$(WARN_COLOR)-----------------------------------------------------------$(NO_COLOR)"
clean:
	@echo "$(ERROR_COLOR)-----------------------------------------------------------$(NO_COLOR)"
	@rm -f $(SRO)
	@rm -f $(addprefix obj/, $(SRO))
	@echo "\tDeleting all object-files $(OK_COLOR)           [done]$(NO_COLOR)"
	@echo "$(ERROR_COLOR)-----------------------------------------------------------$(NO_COLOR)"

fclean: clean
	@echo "$(ERROR_COLOR)-----------------------------------------------------------$(NO_COLOR)"
	@rm -f $(NAME) $(LIBFT)
	@echo "\tDeleting libftprintf static library $(OK_COLOR) [done]$(NO_COLOR)"
	@echo "$(ERROR_COLOR)-----------------------------------------------------------$(NO_COLOR)"

re: fclean all
