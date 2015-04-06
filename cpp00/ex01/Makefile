SRC		=	Phonebook.cpp \
			Contact.cpp \
			main.cpp
OBJ		=	Phonebook.o \
			Contact.o \
			main.o
INC		=	-I./
FLAGS	=	-Wall -Wextra -Werror
NAME	=	phonebook
CC		=	g++

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $@

$(OBJ):
	@$(CC) $(FLAGS) $(INC) -c $(SRC)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all