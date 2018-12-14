####################################################
# Generic makefile
# for compiling and linking C++ projects on Linux
####################################################
### Customising
#
# Adjust the following if necessary; EXECUTABLE is the target
# executable's filename, and LIBS is a list of libraries to link in
# (e.g. alleg, stdcx, iostr, etc). You can override these on make's
# command line of course, if you prefer to do it that way.
#
#
EXECUTABLE := unittest
LIBDIR:=
LIBS := check
INCLUDES:= include
SRCDIR:= tests tests/list tests/tree tests/queue src/list src/tree src/queue \
	src/hash
BIN := bin
DOC := docs
DOXYFILE := DOXYFILE
#
# # Now alter any implicit rules' variables if you like, e.g.:

CC := gcc
CFLAGS := -g -Wall --std=gnu11
CFLAGS += $(addprefix -I,$(INCLUDES))
#
# # The next bit checks to see whether rm is in your djgpp bin
# # directory; if not it uses del instead, but this can cause (harmless)
# # `File not found' error messages. If you are not using DOS at all,
# # set the variable to something which will unquestioningly remove
# # files.
#

RM-F := rm -rf


# # You shouldn't need to change anything below this point.
#
SRCS := $(wildcard *.c) $(wildcard $(addsuffix /*.c, $(SRCDIR)))
OBJS := $(patsubst %.c,%.o,$(SRCS))


.PHONY : all docs objs clean deepclean rebuild info

all: $(EXECUTABLE)

docs:
	@doxygen $(DOXYFILE)

objs : $(OBJS)

clean :
	$(RM-F) $(OBJS)
deepclean: clean
	$(RM-F) $(BIN)
	$(RM-F) $(DOC)

rebuild: deepclean all
$(EXECUTABLE) : $(OBJS)
	@mkdir -p $(BIN)
	$(CC) -o $(BIN)/$(EXECUTABLE) $(OBJS) $(addprefix -L,$(LIBDIR)) $(addprefix -l,$(LIBS))
	@$(BIN)/$(EXECUTABLE)

info:
	@echo $(SRCS)
	@echo $(OBJS)
