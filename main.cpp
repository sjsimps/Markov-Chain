
#include <vector>

#include "markov_chain.h"

int main (int argc, char* argv[])
{
    Markov_Chain* chain = new Markov_Chain();

    chain->Parse_File(std::string("test.txt"), &chain->m_data);

    chain->Build_Chain();

    chain->Output_Chain(1,25);

    delete chain;
}
