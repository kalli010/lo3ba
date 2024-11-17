NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -I./include -I$(libft_src) -g -fsanitize=address -g3

CDIRS = src

ODIRS = bin

SRC = $(foreach dir, $(CDIRS), $(wildcard $(dir)/*.c))

OBJ = $(patsubst %.c, $(ODIRS)/%.o, $(notdir $(SRC)))

vpath %.c $(CDIRS)

CL = cl

FCL = fcl

libft_src = ./libs/libft/

libft = $(libft_src)libft.a

all:
	$(call zaki,$(NAME),all)

clean:
	$(call zaki,$(CL),clean)

fclean: 
	$(call zaki,$(FCL),fclean)

$(NAME): $(OBJ) $(libft)
	$(CC) $(CFLAGS) $(OBJ) $(libft) -o $(NAME)

$(ODIRS)/%.o: %.c | $(ODIRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(ODIRS):
	mkdir $(ODIRS)

$(libft):
	make -C $(libft_src) 

$(CL):
	make -C $(libft_src) clean
	rm -fr $(ODIRS)

$(FCL):
	make -C $(libft_src) fclean
	rm -fr $(ODIRS) $(NAME)

re: fclean all

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
        sleep 0.7; \
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
