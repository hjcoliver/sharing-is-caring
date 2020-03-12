// Code to construct a rectangle and square.
// Written by James Oliver on 15th October 2018.

#include "begin.h"
#include "Person.h"
#include "Population.h"

void set_up(int argc, char *argv[], // this function sets up key variables by reading in as main arguments, or asking the user for them.
           int &npop, float &probability_transfer, float &proportion_vaccinated ) {
  if (argc >= 2) { // if the user specifies the population size, set it.
    std::istringstream iss( argv[1] );
    iss >> npop;
  } else { // if they don't specify population size at the command line, ask for it.
    cout << "Enter population size:";
    cin >> npop;
  }
  if (argc >= 3) {  // if the user also specifies the probability of disease transfer, set it
    std::istringstream iss( argv[2] );
    iss >> probability_transfer;
  } else {  // if they don't specify probability at the command line, ask for it.
    cout << "Enter a probability of disease transfer (between 0 and 1):";
    cin >> probability_transfer;
  }
  if (argc >= 4) {  // if the users specifies the proportion of the population that are vaccinated, set it.
    std::istringstream iss( argv[3] );
    iss >> proportion_vaccinated;
  } else {  // if they don't specify vaccination rate at the command line, ask for it.
    cout << "What proportion of the population are vaccinated (between 0 and 1)?";
    cin >> proportion_vaccinated;
  }
}

int main(int argc, char *argv[]) { // main can be called with arguments
  int npop = 10000;
  float probability_transfer = 1.0, proportion_vaccinated = 0.0;
  set_up(argc,argv,npop,probability_transfer,proportion_vaccinated);  // set up key parameters that may be read from command line

  srand( (unsigned)time( NULL ) );  // seed the random number generator.
  ofstream file;  // define output file
  Population population(npop);  // set up the population  

  population.set_probability_of_transfer(probability_transfer);  // set transmission probability
  population.inoculate(proportion_vaccinated);  // vaccinate population randomly
  population.random_infection();  // randomly infect patient zero
  population.open_file(file);  // open output file
  population.wrt_file(file, 0);  // write initial state to output file
  for (int step = 1; ; step++) {  // loop over time
    population.update_spread();  // update status of all people
    population.wrt_file(file,step);  // write status to file
    if (population.count_infected() == 0) { // if nobody is infectious, end the simulation.
      population.print_lrg(step);  // print current status of all people
      break;
    }
  }
  population.close_file(file);  // close output file
  return 0;   //Finished!
}
