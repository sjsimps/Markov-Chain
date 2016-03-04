#Markov Chain Generator
This project produces a [Markov chain](https://en.wikipedia.org/wiki/Markov_chain) given a series of input data.

###How to use this project
The "markov_chain.[cpp,h]" source files are required to use the Markov Chain data structure, which is the primary feature of this repo. These files are made to be integrated with another project easily.

The remainder of this project provides example usage of the Markov Chain structure.

###The Example Program:
This example program generates a Markov chain from text input and outputs a randomized text sequence.

How To Run:
```
./markov [options]

[-f | --file ] <filename>  Generate chain from file.
[-s | --size ] <size>      Set number of words generated.
[-r | --regex] <regex>     Set new regex string filter.
[-c | --csv  ]             Parse input file as CSV file.
[-a | --all  ]             Utilize all input without filter
[-l | --line ]             Use newlines as chain entries
[-h | --help ]             Display help and exit
```

How To Build:
```
    Run "make" within the main directory to build the project.
```
