# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/15 20:55:03 by jpelline          #+#    #+#              #
#    Updated: 2025/10/22 17:25:09 by zfarah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ████████████

# ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ SETTINGS ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ #

# Project configuration
NAME			:= miniRT
CC				:= cc

# Compiler flags
CFLAGS			:= -Wall -Wextra -Werror
DEBUG_FLAGS		:= -g3 -fsanitize=address -fsanitize=undefined
OPTFLAGS		:= -Ofast -ffast-math -march=native -flto -funroll-loops -fomit-frame-pointer

# Directory structure
SRC_DIR			:= src
OBJ_DIR			:= obj
LIB_DIR			:= lib
DEP_DIR			:= $(OBJ_DIR)/.deps

# Libraries
LIBFT_DIR		:= $(LIB_DIR)/libft
LIBFT			:= $(LIBFT_DIR)/libft.a

MLX_PATH		:= $(LIB_DIR)/MLX42/build/
MLX_NAME		:= libmlx42.a
MLX_BPATH		:= MLX42/
MLX				:= $(MLX_PATH)$(MLX_NAME)

# Include paths and libraries
INC				:= -I./include -I$(LIB_DIR)/MLX42/include/MLX42 -I$(LIBFT_DIR)/include

# Dependency generation flags
DEPFLAGS		= -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.d


# Additional flags
LDFLAGS			= -L$(LIBFT_DIR) -lft -L$(MLX_PATH) -lmlx42 \
				-lglfw -lXext -lX11 -lm -ldl -pthread
# 				-ldl /opt/homebrew/opt/glfw/lib/libglfw.dylib -pthread -lm
# ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ VISUAL STYLING ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ #

# Terminal colors for build output
BOLD			:= $(shell tput bold)
GREEN			:= $(shell tput setaf 2)
YELLOW			:= $(shell tput setaf 3)
BLUE			:= $(shell tput setaf 4)
MAGENTA			:= $(shell tput setaf 5)
CYAN			:= $(shell tput setaf 6)
WHITE			:= $(shell tput setaf 7)
RESET			:= $(shell tput sgr0)

# ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ SOURCE FILES ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ #

# Virtual path
VPATH	:= $(SRC_DIR): \
	$(SRC_DIR)/parsing: \
	$(SRC_DIR)/primitives: \
	$(SRC_DIR)/geometry: \
	$(SRC_DIR)/MLX: \
	$(SRC_DIR)/raytracer \
	$(SRC_DIR)/threads \
	$(SRC_DIR)/textures:

# Parsing and syntax analysis
SRCS_MAIN := \
	main.c \
	parsing.c \
	parse_ambient.c \
	parse_camera.c \
	parse_cylinder.c \
	parse_light.c \
	parse_paraboloid.c \
	parse_plane.c \
	parse_sphere.c \
	parse_textures.c \
	parsing_utility.c \
	color.c \
	viewport.c \
	vec3d.c \
	raytracer.c \
	sphere.c \
	fps.c \
	key_hooks.c \
	plane.c \
	hit.c \
	threads.c \
	rotation.c \
	move_camera.c \
	move_objects.c \
	scale_objects.c \
	vector.c \
	light.c \
	cylinder.c \
	circle.c \
	orthonormal_basis.c \
	phong.c \
	ray.c \
	paraboloid.c \
	plane_uv.c \
	texture.c \
	sphere_uv.c

# Combine all source files
SRCS := \
	$(SRCS_MAIN)

# ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ BUILD VARIABLES ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ #

# Object files and build tracking
OBJS				:= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
TOTAL_SRCS			:= $(words $(SRCS))

# Build markers and progress tracking
MARKER_STANDARD		:= .standard_build
PROGRESS_FILE		:= $(OBJ_DIR)/.progress

# Utility variables for build optimization
LATEST_SRC			:= $(shell find src -name "*.c" | \
							xargs ls -t 2>/dev/null | head -1)
OBJ_FILES_EXIST		:= $(shell [ -n "$(wildcard $(OBJ_DIR)/*.o)" ] && echo yes)

# Looking for updated header files
LATEST_HEADER		:= $(shell find include \
							-name "*.h" 2>/dev/null | xargs ls -t \
							2>/dev/null | head -1)

# Check if binary is up to date
is_up_to_date = \
	[ -f $(NAME) ] && \
	[ "$(NAME)" -nt $(LATEST_SRC) ] && \
	[ "$(NAME)" -nt $(LATEST_HEADER) ] && \
	[ "$(OBJ_FILES_EXIST)" = "yes" ]

# ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ BUILD TARGETS ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ #

# Default target with intelligent rebuild detection
all:
	@if [ -f $(MARKER_STANDARD) ] && $(is_up_to_date) 2>/dev/null; then \
		echo ">$(BOLD)$(YELLOW) $(NAME) is already up to date.$(RESET)"; \
	else \
		echo ">$(BOLD)$(WHITE) Starting to build $(NAME)...$(RESET)"; \
		$(MAKE) $(NAME) --no-print-directory; \
		touch $(MARKER_STANDARD); \
		echo ">$(BOLD)$(GREEN) All components built successfully!$(RESET)"; \
	fi

# Main executable linking with dependency checking
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo ">$(BOLD)$(GREEN) Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(OPTFLAGS) $(LDFLAGS) 
	@touch $(MARKER_STANDARD)
	@rm -f $(PROGRESS_FILE)
	@echo ">$(BOLD)$(GREEN) $(NAME) successfully compiled!$(RESET)"

# Individual object file compilation with progress tracking
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR) $(DEP_DIR)
	@if [ -f $(PROGRESS_FILE) ]; then \
		CURRENT=$$(cat $(PROGRESS_FILE)); \
		NEXT=$$((CURRENT + 1)); \
		echo "$$NEXT" > $(PROGRESS_FILE); \
		printf "> [%3d%%] $(CYAN)(%d/%d files) Compiling $<... $(RESET)\n" \
			$$((NEXT*100/$(TOTAL_SRCS))) $$((NEXT)) $(TOTAL_SRCS); \
	fi
	@$(CC) $(CFLAGS) $(OPTFLAGS) $(DEPFLAGS) -c $< -o $@ $(INC)

# ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ ADDITIONAL TARGETS ■■■■■■■■■■■■■■■■■■■■■■■■■■ #

# Directory creation and dependency management
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "0" > $(PROGRESS_FILE)

# Include auto-generated dependency files
-include $(wildcard $(DEP_DIR)/*.d)

$(DEP_DIR): | $(OBJ_DIR)
	@mkdir -p $@

# build libft if needed
$(LIBFT):
	@echo ">$(MAGENTA) Building libft library...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIR) --no-print-directory

# Build MLX42 if needed
$(MLX):
	@echo "$(CYAN) Building MLX42 library...$(RESET)"
	@cd $(LIB_DIR) && \
	git clone -q --depth 1 \
	--branch v2.4.1 \
	--single-branch \
	https://github.com/codam-coding-college/MLX42.git > /dev/null 2>&1
	@echo "$(BOLD)$(GREEN)✅ MLX42 successfully cloned!$(RESET)"
	@cd $(LIB_DIR)/$(MLX_BPATH) && cmake -B build > /dev/null 2>&1
	@echo "$(BOLD)$(GREEN)✅ MLX42 successfully built to ./lib/MLX42/build$(RESET)"
	@$(MAKE) -sC $(MLX_PATH) --no-print-directory
	@echo "$(BOLD)$(GREEN)✅ $(MLX) successfully compiled!$(RESET)"

# Development and debugging build configuration
debug: CFLAGS	+= $(DEBUG_FLAGS)
debug: OPTFLAGS	:= -O0
debug: clean $(NAME)
	@echo ">$(BOLD)$(CYAN) Debug build completed!$(RESET)"

# ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ CLEAN TARGETS ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ #

# Remove object files and build artifacts
clean:
	@if [ -d $(OBJ_DIR) ]; then \
		echo "> [ $(NAME) ] $(YELLOW) Cleaning object files...$(RESET)"; \
		rm -rf $(OBJ_DIR); \
		printf "> [ %-5s ] %b %s Object files cleaned!%b\n" "$(NAME)" \
		"$(YELLOW)" "$(NAME)" "$(RESET)"; \
	else \
		echo "> [ $(NAME) ] $(BOLD)$(YELLOW) Nothing to be done with \
		$(RESET)$(WHITE)clean$(RESET)"; \
	fi

# Complete cleanup including executables and external libraries
fclean: clean
	@if [ -f $(NAME) ]; then \
		echo "> [ $(NAME) ] $(YELLOW) Removing $(NAME)...$(RESET)"; \
		rm -f $(NAME); \
		rm -f $(MARKER_STANDARD); \
		printf "> [ %-5s ] %b %s removed!%b\n" "$(NAME)" "$(YELLOW)" \
		"$(NAME)" "$(RESET)"; \
	else \
		echo "> [ $(NAME) ] $(BOLD)$(YELLOW) Nothing to be done with \
		$(RESET)$(BOLD)$(WHITE)fclean$(RESET)"; \
	fi
	@if [ -f $(LIBFT) ]; then \
		$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory; \
	else \
		echo "> [ libft     ] $(BOLD)$(YELLOW) Nothing to be done with \
		$(RESET)$(BOLD)$(WHITE)fclean$(RESET)"; \
	fi

# Full rebuild from clean slate
re:
	@echo "> [ $(NAME) ] $(BOLD)$(WHITE) Rebuilding from scratch...$(RESET)"
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) $(NAME) --no-print-directory

# ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ TARGET DECLARATIONS ■■■■■■■■■■■■■■■■■■■■■■■■■ #

# Preserve intermediate object files and declare phony targets
.SECONDARY: $(OBJS)
.PHONY: all debug clean fclean re
