PROG = trainingApp
CC = g++
AR = ar
CPPFLAGS = -g -Wall -v
LDFLAGS =
BIN = ./bin
OBJ = ./obj
INC = -I ./ext/DataStructure \
      -I ./src/Date          \
      -I ./src/Training      \
      -I ./src/Db            \
      -I ./src/logger
INC_LIB = -L $(LIB)
LIB = ./ext/DataStructure
DATA_STRUCTURE_LIB_NAME = dataStructure
DATA_STRUCTURE_LIB = lib$(DATA_STRUCTURE_LIB_NAME).a

OBJS = Date.o TrainingDuration.o Logger.o Training.o DbManager.o main.o 

LIST_OBJS=$(addprefix $(OBJ)/, $(OBJS))

default: $(PROG)

$(PROG) : $(LIST_OBJS)
	$(CC) $(LDFLAGS) $(LIST_OBJS) -o $(BIN)/$(PROG) $(INC_LIB) -l $(DATA_STRUCTURE_LIB_NAME) -l sqlite3

$(OBJ)/main.o: src/main.cpp 
	$(CC) $(INC) $(CPPFLAGS) -c $< -o $@

$(OBJ)/Logger.o: src/logger/Logger.cpp
	$(CC) $(CPPFLAGS) $(INC) -c $< -o $@

$(OBJ)/DbManager.o: src/Db/DbManager.cpp
	$(CC) $(CPPFLAGS) $(INC) -c $< -o $@

$(OBJ)/Training.o: src/Training/Training.cpp
	$(CC) $(CPPFLAGS) $(INC) -c $< -o $@

$(OBJ)/TrainingDuration.o: src/Date/TrainingDuration.cpp
	$(CC) $(CPPFLAGS) $(INC) -c $< -o $@

$(OBJ)/Date.o: src/Date/Date.cpp
	$(CC) $(CPPFLAGS) $(INC) -c $< -o $@

clean:
	rm -dfr $(BIN)/*  $(OBJ)/*
