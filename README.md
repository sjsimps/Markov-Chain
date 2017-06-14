# Markov Chain
This project provides a [Markov chain](https://en.wikipedia.org/wiki/Markov_chain) data structure to be
incorporated into other projects, and also provides a Markov chain utility that may be used to test the chain's functionality.

### Markov Chain Data Structure:

To use the data structure in your own project, include
[Markov_Chain/markov_chain.h](https://github.com/sjsimps/Markov-Chain/blob/master/Markov_Chain/markov_chain.h)
into your code.

[This readme](https://github.com/sjsimps/Markov-Chain/blob/master/Markov_Chain/README.md) has additional information on how to use the markov chain data structure.

### Markov Chain: Graph Visualization

![alt_tag](https://github.com/sjsimps/Markov-Chain/blob/master/Test/rock_paper_scissors.png)

The Markov chain structure may export to graphviz .dot format. To see an example visualization, run the "visualize" script:
```
~/Development/Markov$ bash visualize
Please enter input file:
Test/rock_paper_scissors.txt
```

To visualize the Markov chain, [xdot](https://apps.ubuntu.com/cat/applications/natty/xdot/) must be
installed, or another graphviz visualization tool must be used.

### Markov Chain: Randomized Output

The Markov chain utility may be used to generate a randomized sequence of data given the probability mappings
of the Markov chain. Here's an example use case that [generates randomized New York Times headlines](https://github.com/sjsimps/NY-Times-Headline-Generator).

### Markov Chain Utility: Usage

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
