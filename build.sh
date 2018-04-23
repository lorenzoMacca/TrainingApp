rm trainingApp
g++ -v  src/*.cpp -L "ext/DataStructure" -l dataStructure -o trainingApp -I "ext/DataStructure"
