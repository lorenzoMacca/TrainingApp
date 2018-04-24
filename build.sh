rm trainingApp
g++ -v  src/*.cpp src/db/*.cpp -L "ext/DataStructure" -l dataStructure -o trainingApp -I "ext/DataStructure"
