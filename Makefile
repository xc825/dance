BIN_DIR := bin
SRC_DIR := src
OBJ_DIR := obj
INC_DIR := include
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS := 
#CPPFLAGS := -g
#CPPFLAGS += -fPIE
#CPPFLAGS += -no-pie
CPPFLAGS += -std=c++2a
CXXFLAGS := 
COMPILER := clang++
#COMPILER := c++
LOG_LVL := 5
WARN := -Wall
#WARN += -Wzero-as-null-pointer-constant

all: party

#generate: generate.o
#	$(COMPILER) $(LDFLAGS) $(CPPFLAGS) -o $(BIN_DIR)/$@ $^

party: $(OBJ_FILES)
	$(COMPILER) $(LDFLAGS) $(CPPFLAGS) -o $(BIN_DIR)/$@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(COMPILER) $(CPPFLAGS) $(CXXFLAGS) $(WARN) -I $(INC_DIR) -DLOG_LVL=$(LOG_LVL) -c -o $@ $<


SUBDIRSCLEAN=$(addsuffix clean,$(OBJ_DIR))

clean: $(SUBDIRSCLEAN)
	rm -fv bin/*

clean_curdir:
	rm -rfv *.o

%clean: %
	$(MAKE) -C $< -f $(PWD)/Makefile clean_curdir
