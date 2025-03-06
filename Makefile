# Makefile generated by Make My File: https://github.com/MathysCogne/Make_My_File-42
# Date of generation: 16-02-2025 19:24:38

# 📄 Documentation:
# This Makefile is generated automatically by the Make My File program.
# It facilitates the compilation of C programs.
# For further details on Makefile usage, you can consult the official GNU Make documentation:
# https://www.gnu.org/software/make/manual/make.html 
#
# 🔧 Variables:
# - NAME: Name of the executable or library to create.
# - SRCDIR: Directory where the source (.c) files are located.
# - OBJDIR: Directory where object files will be stored.
# - INCDIR: Directory containing header (.h) files for inclusion.
# - SRC: List of source files to compile.
# - OBJ: Object files generated from the source files.
# - CC: The compiler to use. Default is 'cc', but you can modify it if needed.
# - CFLAGS: Compilation flags (default includes warnings and debugging).
# - LDFLAGS: Linker flags (if any).
# - LIBS: Libraries to link against.
# - LIBFT_DIR: Directory where Libft is located.
# - MINILIBX_DIR: Directory where MiniLibX will be cloned automatically.
#
# 🚀 Rules:
# - 'make': Compiles the entire project by generating the executable defined in NAME.
# - 'make clean': Deletes only the compiled object (.o) files, keeping the executable.
# - 'make fclean': Deletes all generated files, including the executable and object files.
# - 'make re': Cleans (fclean) and then rebuilds the project from scratch.
# - 'make bonus': Compiles additional bonus source files if defined in the project.
# - 'make regen': Re-generates the Makefile if Make My File configuration has changed.
#
# 📚 Usage of Libft:
# - Default Directory: 'libft'.
# - If your Libft is located in a different directory, customize the 'LIBFT_DIR' variable in the Makefile accordingly.
# - Include the header in your source files: #include "libft.h"
# - Example usage: int result = ft_strlen("Hello");
#
# 🖼️ Usage of MiniLibX:
# - MiniLibX will be cloned and included automatically. Choose this option during configuration.
# - Include the header in your source files: #include "mlx.h"
# - Example usage: mlx_init();
#
# 💡 Tips:
# - Use 'VERBOSE=1' when running make (e.g., 'make VERBOSE=1') to see detailed command outputs.
#
# Please report any bugs or suggestions at: https://github.com/MathysCogne/Make_My_File-42/issues

NAME = minishell

SRCDIR = src
OBJDIR = obj
INCDIR = include

# Source Files
SRC = main.c\
		parsing/parsing.c\
		parsing/node_init.c\
		parsing/tokenize.c\
		parsing/tokenize2.c\
		parsing/tokenize3.c\
		parsing/tokenize_utils.c\
		parsing/tokenize_utils2.c\
		parsing/tokenize_utils3.c\
		parsing/for_test.c\
		parsing/parse.c\
		parsing/parse_tokens.c\
		parsing/commands.c\
		parsing/free_struct.c

OBJ = $(SRC:.c=.o)
SRC := $(addprefix $(SRCDIR)/, $(SRC))
OBJ := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(OBJ))

# Libft - Please configure your own path if different
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE := $(LIBFT_DIR)#/include 		#Your header file in include dir ?
# Libraries and Linker Flags
LDFLAGS =  -L$(LIBFT_DIR)
LIBS =  $(LIBFT)

# Archiver
AR = ar
ARFLAGS = rcs

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -g3 -I$(LIBFT_INCLUDE)

# Compilation mode (silent by default, set VERBOSE=1 to show commands)
VERBOSE ?= 0
ifeq ($(VERBOSE),1)
  V := 
else
  V := @
endif

# Colors
RED     := "\033[1;31m"
GREEN   := "\033[1;32m"
RESET   := "\033[0m"



# Default Rule
all: $(OBJDIR) $(LIBFT) $(NAME)

# Object Directory Rule
$(OBJDIR):
	$(V)mkdir -p $(OBJDIR) || true

# Dependency Files
DEP = $(OBJ:.o=.d)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(V)$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEP)

# Linking Rule
$(NAME): $(OBJ) $(LIBFT)
	$(V)$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(BONUS_OBJ) $(LIBS) $(MLXFLAGS) -o $(NAME)
	$(V)echo $(GREEN)"[$(NAME)] Executable created ✅"$(RESET)

# Libft
$(LIBFT):
	$(V)$(MAKE) --silent -C $(LIBFT_DIR)
	$(V)echo '[$(NAME)] Libft build successfully'

# Clean Rules
clean:
	$(V)echo $(RED)'[$(NAME)] Cleaning objects'd$(RESET)
	$(V)rm -rf $(OBJDIR)

fclean: clean
	$(V)echo $(RED)'[$(NAME)] Cleaning all files'$(RESET)
	$(V)rm -f $(NAME)
	$(V)$(MAKE) --silent -C $(LIBFT_DIR) fclean

re: fclean all

# Makefile Reconfiguration 
regen:
	makemyfile

.PHONY: all clean fclean re bonus regen
.DEFAULT_GOAL := all
