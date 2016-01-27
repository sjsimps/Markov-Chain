
#include <vector>
#include <getopt.h>

#include "markov_chain.h"

static std::string file = "test.txt";

static void set_config(int argc, char* argv[])
{
    int option_index;
    static struct option options[] =
    {
        {"file",       required_argument, 0, 'f'},
        {"help",       no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((option_index = getopt_long(argc, argv, "hf:", options, NULL)) != -1)
    {
        switch (option_index){
            case 'f':
                file = optarg;
                break;
            case 'h':
                std::cout << "\nUsage: markov [fh]"
                          << "\n"
                          << "\n\t[-f | --file] <filename>  Generate chain from file"
                          << "\n\t[-h | --help]             Display help and exit."
                          << "\n\n";
                exit(EXIT_SUCCESS);
                break;
            default:
                std::cout<< "\nInvalid option. Program exiting.\n";
                exit(EXIT_FAILURE);
                break;
        }
    }
}

int main (int argc, char* argv[])
{
    set_config(argc, argv);

    Markov_Chain* chain = new Markov_Chain();

    chain->Parse_File(file, &chain->m_data);
    chain->Build_Chain();
    chain->Output_Chain(1,25);

    delete chain;
}
