CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
LDFLAGS	=
LDLIBS	=

SUFFIX	= .o
NAME	= libftprintf.a

# DEBUG routine
ifeq ($(BUILD), Debug)
	#CFLAGS	+= -fsanitize=address -g -O0 -D DEBUG
	CFLAGS	+= -g -O0 -D DEBUG
	SUFFIX	= .debug.o
endif

# OS flags
ARCH	= $(shell uname -m)
OS		= $(shell uname -s)

ifeq ($(OS), Darwin)
	LDLIBS +=
endif

ifeq ($(OS)_$(ARCH), Linux_x86_64)
	CFLAGS += -D LINUX
	LDLIBS +=
else ifeq ($(OS), Linux)
	CFLAGS += -D LINUX
	LDLIBS +=
endif

SRC_PREFIX = ./src/
OBJ_PREFIX = ./obj/

SRC		=	parse \
			buffer \
			print_formated_string \
			print_formated_digit \
			print_formated_hex \
			print_formated_unsigned \
			print_formated_space \
			print_formated_char \
			print_formated_widechar \
			print_formated_octal \
			print_formated_pointer \
			ft_printf \
			ft_eprintf \
			ft_dprintf \
			ft_fprintf \
			ft_asprintf \
			ft_sprintf \
			ft_snprintf \
			ft_wstrlen \
			ft_wstrcpy \
			ft_isdigit \
			ft_isspace \
			ft_strdel \
			ft_strlen \
			ft_strncpy \
			ft_strnew \
			ft_strchr \
			ft_strjoin \
			ft_strdup \
			ft_strpbrk \
			ft_toupper \
			ft_atoi \
			ft_itoa \
			ft_imaxtoa \
			ft_uitoa \
			ft_itoa_base

ifeq ($(BUILD), Debug)
	SRC +=
endif

SRC := $(addsuffix .c, $(SRC))
SRC := $(addprefix $(SRC_PREFIX), $(SRC))

OBJ = $(subst $(SRC_PREFIX), , $(SRC:.c=$(SUFFIX)))
OBJ := $(addprefix $(OBJ_PREFIX), $(OBJ))

.PHONY: all clean fclean re debug

all: $(NAME)

debug:
	@$(MAKE) BUILD=Debug all

$(NAME): $(OBJ)
	@echo "making $@"
	@ar rc $@ $^
	@ranlib $(NAME)

$(OBJ_PREFIX)%$(SUFFIX): $(SRC_PREFIX)%.c
	@echo "making $@"
	@mkdir -p $(OBJ_PREFIX)
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	/bin/rm -rf $(OBJ_PREFIX)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
