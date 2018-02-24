# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/19 20:53:51 by spopieul          #+#    #+#              #
#    Updated: 2018/02/24 15:45:45 by spopieul         ###   ########.fr        #
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

LIBFT_FILES += $(addprefix char/, \
	ft_tolower ft_islower ft_isdigit ft_isspace \
	ft_isupper ft_toupper \
)

LIBFT_FILES += $(addprefix conversion/, \
	ft_atoll ft_lltoa ft_ulltoa ft_wctoa \
)

LIBFT_FILES += $(addprefix memory/, \
)

LIBFT_FILES += $(addprefix string/, \
	ft_strlen ft_strcpy ft_strncpy ft_strtolower \
	ft_strcmp ft_strrev ft_strfind ft_striter \
)

LIBFT_FILES += $(addprefix unicode/, \
	ft_wclen ft_wstrtoa_len ft_wstrtoa_len_n \
)

LIBFT_ODIR 	= $(LIBFT_DIR)/objs
LIBFT_SDIR 	= $(LIBFT_DIR)/srcs

LIBFT_INC	= -I $(LIBFT_DIR)/includes

$(LIBFT_ODIR)/%.o: $(LIBFT_SDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) -c $(LIBFT_INC) -o $@ $< $(CFLAGS)

# PRINTF
# -------------

PRINTF_DIR		= .
PRINTF_FILES	= buffer color convert format format2 ft_printf parse utils write

PRINTF_ODIR 	= $(PRINTF_DIR)/objs
PRINTF_SDIR 	= $(PRINTF_DIR)/srcs

PRINTF_INC		= -I $(PRINTF_DIR)/includes

$(PRINTF_ODIR)/%.o: $(PRINTF_SDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) -c $(PRINTF_INC) $(LIBFT_INC) -o $@ $< $(CFLAGS)

# MAKE
# -------------

NAME 	= libftprintf.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
OBJS 	=\
	$(call get_objs, $(LIBFT_ODIR), $(LIBFT_FILES)) \
	$(call get_objs, $(PRINTF_ODIR), $(PRINTF_FILES))

$(NAME): $(make_libft) $(OBJS)
	@ar rvs $(NAME) $^

all: $(NAME)

clean:
	/bin/rm -rf $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
