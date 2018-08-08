rm trainingApp
g++ -g src/Utils/*.cpp \
       src/User/*.cpp  \
       src/*.cpp \
       src/db/*.cpp \
       src/logger/*.cpp \
       src/Date/*.cpp \
       src/Training/*.cpp \
       src/Training/TrainingType/*.cpp \
   -L "ext/DataStructure" \
   -l dataStructure \
   -l sqlite3 \
   -o trainingApp \
   -I "ext/DataStructure" \
   -I "src/Training/" \
   -I "src/Training/TrainingType" \
   -I "src/logger/" \
   -I "src/db/" \
   -I "src/Date/" \
   -I "src/User/" \
   -I "src/Utils/"
