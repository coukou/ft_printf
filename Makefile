# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/19 20:53:51 by spopieul          #+#    #+#              #
#    Updated: 2018/02/14 11:13:19 by spopieul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# $(1): folder
# $(2): files
define get_objs
	$(addprefix $(1)/, $(addsuffix .o, $(2)))
endef

# LIBFT
# -------------

LIBFT_DIR	= libft

LIBFT_FILES	+= $(addprefix char/, \
	ft_toupper ft_tolower ft_isdigit ft_isspace \
	ft_isupper ft_islower \
)

LIBFT_FILES	+= $(addprefix conversion/, \
	ft_lltoa ft_ulltoa ft_atoll ft_wctoa \
)

LIBFT_FILES	+= $(addprefix string/, \
	ft_strtolower ft_strcpy ft_strcmp ft_strlen \
	ft_strncpy ft_striter ft_strfind ft_strrev \
)

LIBFT_FILES	+= $(addprefix unicode/, \
	ft_wstrtoa_len_n ft_wstrtoa_len ft_wclen \
)

LIBFT_ODIR 	= $(LIBFT_DIR)/objs
LIBFT_SDIR 	= $(LIBFT_DIR)/srcs

LIBFT_INC	= -I $(LIBFT_DIR)/includes

$(LIBFT_ODIR)/%.o: $(LIBFT_SDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) -c -ggdb $(LIBFT_INC) -o $@ $< $(CFLAGS)

# PRINTF
# -------------

PRINTF_DIR		= .
PRINTF_FILES	= \
	buffer color convert format \
	format2 ft_printf parse utils \
	write

PRINTF_ODIR 	= $(PRINTF_DIR)/objs
PRINTF_SDIR 	= $(PRINTF_DIR)/srcs

PRINTF_INC		= -I $(PRINTF_DIR)/includes

$(PRINTF_ODIR)/%.o: $(PRINTF_SDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) -c -ggdb $(PRINTF_INC) $(LIBFT_INC) -o $@ $< $(CFLAGS)

# MAKE
# -------------

NAME 	= libftprintf.a
CC		= gcc
CFLAGS	= -Wall -Wextra # -Werror
OBJS 	=\
	$(call get_objs, $(LIBFT_ODIR), $(LIBFT_FILES)) \
	$(call get_objs, $(PRINTF_ODIR), $(PRINTF_FILES))

$(NAME): $(make_libft) $(OBJS)
	@ar rvs $(NAME) $^ > /dev/null

all: $(NAME)

clean:
	@/bin/rm -rf $(OBJS)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
