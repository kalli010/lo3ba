#the main fail name
NAME = cub3D

#wich compiler you prefer
CC = cc

#the flags that i need
CFLAGS = -Wall -Wextra -Werror -I./include -I$(libft_src) -I$(minilibx_src) -g -fsanitize=address -g3

#creat source and object files
CDIRS = src
ODIRS = bin
SRC = $(foreach dir, $(CDIRS), $(wildcard $(dir)/*.c))
OBJ = $(patsubst %.c, $(ODIRS)/%.o, $(notdir $(SRC)))
vpath %.c $(CDIRS)

#clean
CL = cl

#fclean
FCL = fcl

#librarys
minilibx_src = ./libs/minilibx-linux/
minilibx = $(minilibx_src)libmlx_Linux.a
libft_src = ./libs/libft/
libft = $(libft_src)libft.a

#creat cub3D file
all:
	$(call zaki,$(NAME),all)

#clean all the object files
clean:
	$(call zaki,$(CL),clean)

#clean the object files and cub3D file
fclean: 
	$(call zaki,$(FCL),fclean)

#the rule to creat cub3D file
$(NAME): $(OBJ) $(libft) $(minilibx)
	$(CC) $(CFLAGS) $(OBJ) $(libft) -o $(NAME)

#how to creat the object files
$(ODIRS)/%.o: %.c | $(ODIRS)
	$(CC) $(CFLAGS) -c $< -o $@

#creat the object files folder
$(ODIRS):
	mkdir $(ODIRS)

#creat libft.a
$(libft):
	make -C $(libft_src) 

#creat minilibx_linux.a
$(minilibx):
	make -C $(minilibx_src)

#how to clear files
$(CL):
	make -C $(minilibx_src) clean
	make -C $(libft_src) clean
	rm -fr $(ODIRS)

#how to remove the object files and the main file
$(FCL):
	make -C $(libft_src) fclean
	rm -fr $(ODIRS) $(NAME)

#target to fclean every think and re compiling from the begining
re: fclean all

#reusable scripe to made an animation when make a target
define zaki
@if [ "$2" = "bonus" ] || [ "$2" = "all" ]; then \
	if make -q $1; then \
	    echo "$1 is up to date."; \
			exit 0; \
	fi; \
fi; \
bash -c ' \
MK="make $1"; \
LOGFILE=$$(mktemp); \
$$MK >$$LOGFILE 2>&1 & MK_PID=$$!; \
echo -n "Compiling $2"; \
while kill -0 $$MK_PID 2>/dev/null; do \
    for i in {1..3}; do \
        echo -n "."; \
        sleep 0.5; \
    done; \
    echo -ne "\rCompiling $2   \rCompiling $2"; \
done; \
wait $$MK_PID; \
STATUS=$$?; \
if [ $$STATUS -ne 0 ]; then \
    echo -e "\r$2 failed. See the output below:"; \
    cat $$LOGFILE; \
else \
    echo -e "\r$2 finished.    "; \
fi; \
rm -f $$LOGFILE; \
'; 
endef

.PHONY: all clean fclean re

.SECONDARY:
