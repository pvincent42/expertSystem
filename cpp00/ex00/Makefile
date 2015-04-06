SRC		=	megaphone.cpp
OBJ		=	megaphone.o
FLAGS	=	-Wall -Wextra -Werror
NAME	=	megaphone
CC		=	g++

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $@

$(OBJ):
	@$(CC) $(FLAGS) -c $(SRC)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all