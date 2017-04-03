export COMPILER = clang++
export FLAGS = -MMD -std=c++11 -w -c -g
CPP_FILES = $(wildcard *.cpp)
TOP_DIR = $(notdir $(CPP_FILES:.cpp=.o))
OBJ_FILES := $(shell find -name '*.o')
LINK = -lcurses -lpessum
NAME = ostendo

all: $(TOP_DIR) subsystem $(NAME)
	@setterm -fore green
	@printf "==========>>>>>>>>>>Compiled $(NAME)<<<<<<<<<<==========\n"
	@setterm -fore white

$(NAME): $(TOP_DIR) $(OBJ_FILES)
	@setterm -fore red
	@printf ">>>>>>>>>>----------Core Compile----------<<<<<<<<<<\n"
	@setterm -fore white
	$(COMPILER) $(OBJ_FILES) -o $(NAME) $(LINK)

%.o: %.cpp
	$(COMPILER) $(FLAGS) -o $(notdir $*).o $*.cpp

.PHONY : subsystem
subsystem:
	@cd ostendo_files && $(MAKE)

.PHONY : clean
clean:
	@setterm -fore red
	@printf "Removing *.o files\n"
	@find . -name "*.o" -type f -delete
	@printf "Removing *.d files\n"
	@find . -name "*.d" -type f -delete
	@printf "Removed all *.o and *.d files\n"
	@setterm -fore white

.PHONY : new
new: clean all

.PHONY : log
log:
	@less output.log

.PHONY : lib
lib: all
	@printf "Comiling lib...\n"
	@ar rcs lib$(NAME).a $(OBJ_FILES)
	@printf "Copying lib to /usr/local/lib/...\n"
	@sudo cp lib$(NAME).a /usr/local/lib/ -u
	@printf "Copying base headers to /usr/local/include/...\n"
	@sudo cp *.h /usr/local/include/
	@printf "Copying project headers to /usr/local/include/...\n"
	@sudo find . -name '*.hpp' -exec cp --parents \{\} /usr/local/include/ \;
	@setterm -fore green
	@printf "==========>>>>>>>>>>Compiled Installed Lib<<<<<<<<<<==========\n"
	@setterm -fore white
