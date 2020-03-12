// A code to study a population of people where only a single patient becomes ill.
// Written by James Oliver
#include "begin.h"
#include "Person.h"
#include "Population.h"

int main() {
  srand( (unsigned)time( NULL ) );  // seed the random number generator. 
  int npeople = 5;  // initial population size
  cout << "# people in the population? "; // ask the user for population size
  cin >> npeople;

  Population population(npeople);  // define population
  population.random_infection();  // infect one person
  population.print(0);  // print initial status of population to screen
  for (int step = 1; ; step++) {  // loop over time
    population.update_pop();  // update all population members
    population.print(step);  // print status to screen
    if (population.count_infected() == 0)
      break;  // if nobody is ill, break
  }
  return 0;   //Finished!
}
