PROG = trainingApp
CC = g++
AR = ar
CPPFLAGS = -g -Wall
LDFLAGS =
BIN = ./bin
OBJ = ./obj
INC = ./inc
LIB = ./lib
INC_LIB = -L $(LIB)
INC_PATH = -I $(INC) \
           -I ./ext/DataStructure
INC_EXT_LIB = -L $(EXT_LIB)
EXT_LIB = ./ext/DataStructure
DATA_STRUCTURE_LIB_NAME = dataStructure
DATA_STRUCTURE_LIB = lib$(DATA_STRUCTURE_LIB_NAME).a
TRAINING_LIB_NAME = training
TRAINING_LIB = lib$(TRAINING_LIB_NAME).a

OBJS = WhereCondition.o Session.o Break.o Swim.o Exercise.o GenericExrercise.o UserData.o User.o Shoe.o Run.o Utils.o Date.o TrainingDuration.o Logger.o Training.o DbManager.o

LIST_OBJS=$(addprefix $(OBJ)/, $(OBJS))

default: $(PROG)

$(PROG) : $(TRAINING_LIB) $(OBJ)/main.o
	$(CC) $(LDFLAGS) -o $(BIN)/$(PROG) $(OBJ)/main.o $(INC_EXT_LIB) $(INC_LIB) -l $(DATA_STRUCTURE_LIB_NAME) -l sqlite3 -l $(TRAINING_LIB_NAME)

$(OBJ)/main.o: src/main.cpp
	$(CC) $(INC_PATH) $(CPPFLAGS) -c $< -o $@

$(OBJ)/Logger.o: src/logger/Logger.cpp
	$(CC) $(CPPFLAGS) $(INC_PATH) -c $< -o $@

$(OBJ)/DbManager.o: src/db/DbManager.cpp
	$(CC) $(CPPFLAGS) $(INC_PATH) -c $< -o $@

$(OBJ)/WhereCondition.o: src/db/WhereCondition.cpp
	$(CC) $(CPPFLAGS) $(INC_PATH) -c $< -o $@

$(OBJ)/Training.o: src/Training/Training.cpp
	$(CC) $(CPPFLAGS) $(INC_PATH) -c $< -o $@

$(OBJ)/Break.o: src/Training/Break.cpp
	$(CC) $(CPPFLAGS) $(INC_PATH) -c $< -o $@

$(OBJ)/Session.o: src/Session/Session.cpp
	$(CC) $(CPPFLAGS) $(INC_PATH) -c $< -o $@

$(OBJ)/TrainingDuration.o: src/Date/TrainingDuration.cpp
	$(CC) $(CPPFLAGS) $(INC_PATH) -c $< -o $@

$(OBJ)/Date.o: src/Date/Date.cpp
	$(CC) $(CPPFLAGS) $(INC_PATH) -c $< -o $@

$(OBJ)/Utils.o: src/Utils/Utils.cpp
	$(CC) $(CPPFLAGS) $(INC_PATH) -c $< -o $@

$(OBJ)/Run.o: src/Training/TrainingType/Run.cpp
	$(CC) $(CPPFLAGS) $(INC_PATH) -c $< -o $@

$(OBJ)/Shoe.o: src/Training/TrainingType/Shoe.cpp
	$(CC) $(CPPFLAGS) $(INC_PATH) -c $< -o $@

$(OBJ)/User.o: src/User/User.cpp
	$(CC) $(CPPFLAGS) $(INC_PATH) -c $< -o $@

$(OBJ)/UserData.o: src/User/UserData.cpp
	$(CC) $(CPPFLAGS) $(INC_PATH) -c $< -o $@

$(OBJ)/GenericExrercise.o: src/Training/TrainingType/GenericExrercise.cpp
	$(CC) $(CPPFLAGS) $(INC_PATH) -c $< -o $@

$(OBJ)/Exercise.o: src/Training/TrainingType/Exercise.cpp
	$(CC) $(CPPFLAGS) $(INC_PATH) -c $< -o $@

$(OBJ)/Swim.o: src/Training/TrainingType/Swim.cpp
	$(CC) $(CPPFLAGS) $(INC_PATH) -c $< -o $@

create_training_lib: $(TRAINING_LIB)
	@echo $(TRAINING_LIB) has been compiled.

$(TRAINING_LIB): $(LIST_OBJS)
	@echo Compiling $(TRAINING_LIB)  
	$(AR) -r $(LIB)/$(TRAINING_LIB) $(LIST_OBJS)

clean:
	rm -dfr $(BIN)/*  $(OBJ)/* *.dSYM trainingApp
