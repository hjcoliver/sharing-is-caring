#include "begin.h"
#include "Person.h"
#include "Population.h"

int main() {
  srand( (unsigned)time( NULL ) );  // see the random number generator.
  float probability_transfer = 1.0, proportion_vaccinated = 0.0;
  int npeople = 10;

  cout << "How many people are in your population? ";  // ask user for population size
  cin >> npeople;
  cout << "Enter a probability of disease transfer (between 0 and 1): ";  // ask user for probability of disease transfer
  cin >> probability_transfer;
  cout << "What proportion of the population are vaccinated (between 0 and 1)? "; // ask user for vaccinationrate.
  cin >> proportion_vaccinated;

  Population population(npeople);  // set up the population
  population.set_probability_of_transfer(probability_transfer);  // set probability of disease transfer.
  population.inoculate(proportion_vaccinated); // vaccinate people.
  population.random_infection();  // make one person ill
  population.print(0);  // print current status of all people
  for (int step = 1; ; step++) { // loop over time
    population.update_neighbour();  // update status of all people
    population.print(step);  // print current status of all people
    if (population.count_infected() == 0) { // if nobody is infectious, end the simulation.
       population.print_lrg(step);  // print current status of all people
       break;
    }
  }
  return 0;   //Finished!
}
