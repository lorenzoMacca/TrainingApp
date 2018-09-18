PROG = trainingApp
CC = g++
AR = ar
CPPFLAGS = -g -Wall
LDFLAGS =
BIN = ./bin
OBJ = ./obj
INC = -I ./ext/DataStructure \
      -I ./src/Date          \
      -I ./src/Training      \
      -I ./src/db            \
	  -I ./src/User          \
	  -I ./src/logger        \
	  -I ./src/Training/TrainingType           \
      -I ./src/Utils
INC_LIB = -L $(LIB)
LIB = ./ext/DataStructure
DATA_STRUCTURE_LIB_NAME = dataStructure
DATA_STRUCTURE_LIB = lib$(DATA_STRUCTURE_LIB_NAME).a

OBJS = Swim.o Exercise.o Abs.o UserData.o User.o Shoe.o Run.o Utils.o Date.o TrainingDuration.o Logger.o Training.o DbManager.o main.o

LIST_OBJS=$(addprefix $(OBJ)/, $(OBJS))

default: $(PROG)

$(PROG) : $(LIST_OBJS)
	$(CC) $(LDFLAGS) $(LIST_OBJS) -o $(BIN)/$(PROG) $(INC_LIB) -l $(DATA_STRUCTURE_LIB_NAME) -l sqlite3

$(OBJ)/main.o: src/main.cpp
	$(CC) $(INC) $(CPPFLAGS) -c $< -o $@

$(OBJ)/Logger.o: src/logger/Logger.cpp
	$(CC) $(CPPFLAGS) $(INC) -c $< -o $@

$(OBJ)/DbManager.o: src/db/DbManager.cpp
	$(CC) $(CPPFLAGS) $(INC) -c $< -o $@

$(OBJ)/Training.o: src/Training/Training.cpp
	$(CC) $(CPPFLAGS) $(INC) -c $< -o $@

$(OBJ)/TrainingDuration.o: src/Date/TrainingDuration.cpp
	$(CC) $(CPPFLAGS) $(INC) -c $< -o $@

$(OBJ)/Date.o: src/Date/Date.cpp
	$(CC) $(CPPFLAGS) $(INC) -c $< -o $@

$(OBJ)/Utils.o: src/Utils/Utils.cpp
	$(CC) $(CPPFLAGS) $(INC) -c $< -o $@

$(OBJ)/Run.o: src/Training/TrainingType/Run.cpp
	$(CC) $(CPPFLAGS) $(INC) -c $< -o $@

$(OBJ)/Shoe.o: src/Training/TrainingType/Shoe.cpp
	$(CC) $(CPPFLAGS) $(INC) -c $< -o $@

$(OBJ)/User.o: src/User/User.cpp
	$(CC) $(CPPFLAGS) $(INC) -c $< -o $@

$(OBJ)/UserData.o: src/User/UserData.cpp
	$(CC) $(CPPFLAGS) $(INC) -c $< -o $@

$(OBJ)/Abs.o: src/Training/TrainingType/Abs.cpp
	$(CC) $(CPPFLAGS) $(INC) -c $< -o $@

$(OBJ)/Exercise.o: src/Training/TrainingType/Exercise.cpp
	$(CC) $(CPPFLAGS) $(INC) -c $< -o $@

$(OBJ)/Swim.o: src/Training/TrainingType/Swim.cpp
	$(CC) $(CPPFLAGS) $(INC) -c $< -o $@

clean:
	rm -dfr $(BIN)/*  $(OBJ)/* *.dSYM trainingApp
