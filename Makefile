SRC_PATH	=	src/
OBJ_PATH	=	obj/
INC_PATH	=	inc/
GCC_LOG		=	gcc_log_file.log
SRCS		=	$(shell ls $(SRC_PATH) | grep .cpp$$)
OBJS		=	$(patsubst %.cpp, $(OBJ_PATH)%.o,$(SRCS))
PLATFORM	:=	$(shell uname)
CC			=	g++
HEADER		=	-I./$(INC_PATH)
FLAGS		=	-Ofast -g -Wall -Wextra -Werror -Wno-deprecated-declarations -std=gnu++11 -Wno-unused
VARS		=	-D_DEBUG
NAME		=	expertSys

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(VARS) $(HEADER) $(OBJS) -o $(NAME)

$(patsubst %, $(OBJ_PATH)%,%.o): $(SRC_PATH)$(notdir %.cpp)
	@mkdir -p $(OBJ_PATH)
	@$(CC) -c $(FLAGS) $(VARS) $(HEADER) "$<" -o "$@"

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)

loop:
	@while [ 1 ]; do \
			make re > $(GCC_LOG) 2>&1 ; \
			clear ; \
			cat $(GCC_LOG); \
		if [ -s $(NAME) ] ; then \
			echo "\033[32;1mCompilation done !\033[0m" ; \
			rm -rf $(GCC_LOG); \
			break ; \
		fi ; \
		sleep 1 ; \
	done

config:
	@sed -i '.tmp' 's/expertSys/'"$(NAME)"'/g' Makefile
	@echo "Renamed executable to '"$(NAME)"'"
	@rm -rf Makefile.tmp

re: fclean all

l: re
	@./$(NAME)

launch: l

.PHONY: clean fclean re
