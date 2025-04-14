 SRC =  ft_atoi.c ft_bzero.c ft_calloc.c ft_isascii.c \
       ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_isprint.c \
       ft_memalloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
       ft_memccpy.c ft_memmove.c ft_memset.c ft_memdel.c \
       ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c \
       ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
       ft_tolower.c ft_toupper.c ft_itoa.c ft_putchar_fd.c \
       ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
       ft_striteri.c ft_strjoin.c ft_strmapi.c ft_strtrim.c \
       ft_substr.c ft_strclr.c ft_strdel.c ft_strequ.c \
       ft_strcmp.c ft_strncpy.c ft_strcpy.c ft_strnew.c \
       ft_strstr.c ft_strmap.c ft_strnstr.c ft_memmove.c

 
 NAME  = libft.a
 SRC_DIR = src
 OBJ_DIR = obj

 CC  = cc

 CFLAGS  = -Wall -Werror -Wextra 

 AR = ar

 ARFLAGS = rcs

 SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
 OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)
 
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
