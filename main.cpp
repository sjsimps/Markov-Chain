
#include <vector>
#include <getopt.h>

#include "markov_chain.h"

static std::string file = "test.txt";
static Markov_Chain* chain;
static int out_size = 25;

static void set_config(int argc, char* argv[])
{
    int option_index;
    static struct option options[] =
    {
        {"file",       required_argument, 0, 'f'},
        {"size",       required_argument, 0, 's'},
        {"all",        no_argument, 0, 'a'},
        {"line",      no_argument, 0, 'l'},
        {"help",       no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((option_index = getopt_long(argc, argv, "alhf:s:", options, NULL)) != -1)
    {
        switch (option_index){
            case 'f':
                file = optarg;
                break;
            case 's':
                out_size = strtoul(optarg, NULL, 10);
                break;
            case 'a':
                chain->m_cfg.accept_all = true;
                break;
            case 'l':
                chain->m_cfg.split_lines = true;
                break;
            case 'h':
                std::cout << "\nUsage: markov [options]"
                          << "\nGenerates Markov chain from text input and generates new text sequence."
                          << "\n"
                          << "\n\t[-f | --file] <filename>  Generate chain from file"
                          << "\n\t[-s | --size] <size>      Set number of words generated"
                          << "\n\t[-a | --all ]             Utilize all input without filter."
                          << "\n\t[-l | --line]             Use newlines as chain entries."
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
    chain = new Markov_Chain();

    set_config(argc, argv);

    chain->Parse_File(file, &chain->m_data);
    chain->Build_Chain();
    chain->Output_Chain(1,out_size);

    delete chain;
}
