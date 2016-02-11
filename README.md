#Markov Chain Generator

Generates Markov chain from text input and outputs randomized text sequence.

Usage:

    ./markov [options]

    [-f | --file] <filename>  Generate chain from file
    [-s | --size] <size>      Set number of words generated
    [-c | --csv ]             Parse input file as CSV file.
    [-a | --all ]             Utilize all input without filter
    [-l | --line]             Use newlines as chain entries
    [-h | --help]             Display help and exit

Building:

    Run "make" within the main directory to build the project.
