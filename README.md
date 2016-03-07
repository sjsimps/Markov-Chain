#Markov Chain
This project provides a [Markov chain](https://en.wikipedia.org/wiki/Markov_chain) data structure to be
incorporated into other projects, and also provides a Markov chain utility. To use the data structure in
your own project, simply include [Markov_Chain/markov_chain.h](https://github.com/sjsimps/Markov-Chain/blob/master/Markov_Chain/markov_chain.h)
into your code.

###Markov Chain Utility: Graph Visualization

![alt_tag](https://github.com/sjsimps/Markov-Chain/blob/master/Test/rock_paper_scissors.png)

The Markov chain utility can export to a graphviz file to visualize a markov chain. To
visualize the output of the markov chain there are two options:

1: Run the "visualize" script:
```
~/Development/Markov$ bash visualize
Please enter input file:
Test/rock_paper_scissors.txt
```

2: Run the markov utility with the '-g' option enabled and open the output file with another program:
```
~/Development/Markov$ ./markov -f Test/rock_paper_scissors.txt -g test.dot
~/Development/Markov$ xdot test.dot
```

To visualize the Markov chain, [xdot](https://apps.ubuntu.com/cat/applications/natty/xdot/) must be installed, or another graphviz visualization tool must be used.

###Markov Chain Utility: General

Building:

To build this project, run make on the main directory.

Running:
```
Usage: ./markov -f <input_file> [options]

    [-f | --file ] <filename>  Generate chain from input file.
    [-r | --regex] <regex>     Set new regex string filter.
    [-s | --size ] <size>      Set number of words generated.
    [-g | --graph] <filename>  Generate graphviz output file for chain visualization.
    [-c | --csv  ]             Parse input file as CSV file.
    [-a | --all  ]             Accept all input without regex filter.
    [-l | --line ]             Use newlines as chain entries.
    [-d | --debug]             Print out the status of the chain.
    [-h | --help ]             Display help and exit.
```
