#!/bin/bash

echo "Compiling..."
echo " "
cd src/
g++ -c main.cpp Fibonacci.cpp -I/Documents/SFML/SFML_SRC/include 
echo "Linking..."
echo " "

if [ -e Fibonacci.cpp~ ] ;
then
    rm Fibonacci.cpp~
fi

mv *.o ../linkers
cd ../linkers

g++ main.o Fibonacci.o -o fib -L/Documents/SFML/SFML_SRC/lib -lsfml-graphics -lsfml-window -lsfml-system

mv fib ../
cd ../

if [ -e compile.sh~ ] ;
then 
    rm compile.sh~ 
fi

cd include/
if [ -e *.hh~ ];
then
    rm *.hh~
fi

cd ..
echo "Executing..."
echo " "
./fib

