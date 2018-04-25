rm trainingApp
g++ -v  src/*.cpp src/db/*.cpp src/logger/*.cpp -L "ext/DataStructure" -l dataStructure -l sqlite3 -o trainingApp -I "ext/DataStructure"
