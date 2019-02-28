#FILL IN THE GAPS
CC=g++
LD=ld

TARGET_DIR=bin

DEST=objs
SRC=src
NAME=bxx.exe

CFLAGS:= -std=c++14 -Wsign-compare -Wall -Wextra

INCLUDES_DIR:= -Iinclude
CUSTOM_LIBS_DIR:= 

LIBS= 

##############################
#DO NOT MODIFY ANYTHING BELOW#
##############################

SOURCES = $(wildcard $(SRC)/*.cpp)

OBJS= $(subst $(SRC)/,, $(SOURCES:.cpp=.o) )

CHAIN:= $(CFLAGS)\
$(INCLUDES_DIR)\
$(CUSTOM_LIBS_DIR)\
$(LIBS)

.PHONY: all clean clear rebuild auto

all: link

link: parts
	$(CC)  -o $(TARGET_DIR)/$(NAME) $(addprefix $(DEST)/,$(OBJS)) $(CHAIN)


parts: $(addprefix $(DEST)/,$(OBJS))


$(DEST)/%.o : $(SRC)/%.cpp
	$(CC) -c  $(subst $(DEST),,$<) -o $@ $(CHAIN)

clear: clean

clean:
	rm -r $(DEST) --force
	rm -f $(TARGET_DIR)/$(NAME)
	mkdir $(DEST)

rebuild: clean all

auto:
	mkdir $(DEST)
	mkdir $(TARGET_DIR)
	all

debug:
	echo $(OBJS)
	echo $(SOURCES)