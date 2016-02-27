#Markov Chain Generator
This project produces a Markov chain given a series of input data.

###How to use this project
The "markov_chain.[cpp,h]" and "csv_parser.[cpp,h]" source files are required to use this project.

An example of how to use the Markov Chain Generator can be found within "main.cpp". This program generates a Markov chain from text input and outputs a randomized text sequence.

###How to Run and Build the Example Program:
Running:
```
./markov [options]

[-f | --file] <filename>  Generate chain from file.
[-s | --size] <size>      Set number of words generated.
[-r | --regex] <regex>     Set new regex string filter.
[-c | --csv ]             Parse input file as CSV file.
[-a | --all ]             Utilize all input without filter
[-l | --line]             Use newlines as chain entries
[-h | --help]             Display help and exit
```
Building:
```
    Run "make" within the main directory to build the project.
```
