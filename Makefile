CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
LDFLAGS	=
LDLIBS	=

SUFFIX	= .o
NAME	= libftprintf.a

CORR_FILES = ./Makefile ./src

# DEBUG routine
ifeq ($(BUILD), Debug)
	CFLAGS	+= -fsanitize=address -g -O0 -D DEBUG
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

SRC	=	$(shell ls $(SRC_PREFIX)*.c)

ifeq ($(BUILD), Debug)
	SRC +=
endif

OBJ = $(subst $(SRC_PREFIX), , $(SRC:.c=$(SUFFIX)))
OBJ := $(addprefix $(OBJ_PREFIX), $(OBJ))

.PHONY: all clean fclean re debug correction

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

correction_%:
	@echo "\033[32mCopying libftprintf into \033[33m/tmp/$*\033[0m"
	@mkdir -p /tmp/$*/libftprintf
	@rsync -r --copy-links $(CORR_FILES) /tmp/$*/libftprintf
