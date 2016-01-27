
#include <vector>
#include <getopt.h>

#include "markov_chain.h"

static std::string file = "test.txt";
static Markov_Chain* chain;

static void set_config(int argc, char* argv[])
{
    int option_index;
    static struct option options[] =
    {
        {"file",       required_argument, 0, 'f'},
        {"all",        no_argument, 0, 'a'},
        {"help",       no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((option_index = getopt_long(argc, argv, "ahf:", options, NULL)) != -1)
    {
        switch (option_index){
            case 'f':
                file = optarg;
                break;
            case 'a':
                chain->m_cfg.accept_all = true;
                break;
            case 'h':
                std::cout << "\nUsage: markov [fh]"
                          << "\n"
                          << "\n\t[-f | --file] <filename>  Generate chain from file"
                          << "\n\t[-a | --all]              Utilize all input without filter."
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
    chain->Output_Chain(1,25);

    delete chain;
}
