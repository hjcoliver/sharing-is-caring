bool did_it_spread(float probability_of_transfer) {  // a function to calculate whether a person is infected.
  bool infected = false;
  float bad_luck = (float) rand()/(float)RAND_MAX;  // generate random number to decide if patient is infected.
  if (bad_luck < probability_of_transfer)   // compare the random number to the probability of disease transfer
    infected = true;  // if it is less than the probability of transfer, the person is now infected.
  return infected;
}

class Population {  // define the class for a person
private:
  int npeople;  // size of population
  vector<Person> population;   // vector of people
  float probability_of_transfer;  // probability of disease transmission
public:
  Population( int npeople ) : npeople(npeople), population(vector<Person>(npeople, 0)) {};
  int count_infected() {  // count the number of sick people
    int counter = 0;
    for (int i = 0; i < npeople; i++) {
      if (population[i].getstatus() > 0 || population[i].getstatus() == -3)
        counter++;
    }
    return counter; 
  };
  void random_infection() {  // pick someone at random to infect.
    int bad_luck = rand() % (npeople);  // pick someone at random
    population[bad_luck].infect(5);   // infect them.
  };
  void update_spread() {  // update the status of the population for random spreading of disease.
    for (int i = 0; i < npeople; i++) {
      population[i].update(); 
      if (population[i].getstatus() == -3) // if this person was just infected last step, make infectious.
	population[i].infect(5);
      else if (population[i].getstatus() == 0) { // if this person is susceptible, see if they get infected.
	int interaction_ind = i+1;
	for (int j = 0; j < 6; j++) {  // for each interaction
	  interaction_ind = rand() % (npeople);
	  while (interaction_ind == i)
	    interaction_ind = rand() % (npeople);
	  if (population[interaction_ind].getstatus() > 0) {  // see if they are infectious
	    if (did_it_spread(probability_of_transfer)) {  // see if they transmit the disease.
	      population[i].infect(-3);  // set to -3 so the just-infected can't infect others this time step.
	      break; }
	  } 
	}
      }
    }
  };
  void update_neighbour() {  // update the status of the population for spreading by direct neighbours
    for (int i = 0; i < npeople; i++) {
      population[i].update(); 
      if (population[i].getstatus() == -3) // if this person was just infected last step, make infectious.
	population[i].infect(5);
      else if (population[i].getstatus() == 0) { // if this person is susceptible, see if they get infected.
	int interaction_inds[] = {i-1, i+1};  // array containing the indices of neighbours
	if ( i==0 ) {   // account for people at the end of the vector by "joining the ends".
          interaction_inds[0] = 1; 
	    interaction_inds[1] = npeople - 1; }
	else if ( i == npeople - 1 ) { // account for the other end
	  interaction_inds[0] = 0;
	  interaction_inds[1] = npeople - 2;  }
	for (int j : interaction_inds) {  // for each interaction partner
	  if (population[j].getstatus() > 0) {  // see if they are infectious
	    if (did_it_spread(probability_of_transfer)) {  // see if they transmit the disease.
	      population[i].infect(-3);  // set to -3 so the just-infected can't infect others this time step.
	      break; }
	  } 
	}
      }
    }
  };
  void update_pop() {  // update statuses for the basic disease model used in population development
    for (int i = 0; i < npeople; i++)
      population[i].update();
  };
  void print(int step) { // print display to show who is infected for each time step.
    cout << "In step " << setw(3) << step << ", " << count_infected() << " are sick: ";
    for (int i = 0; i < npeople; i++)
      cout << population[i].status_string() << " "; // for each person, print their status.
    cout << endl;
  };
  void print_lrg(int step) { // print display to show who is infected for each time step for large populations
    int count_inf = 0, count_inoc = 0, count_susc = 0, count_rec = 0;
    for (int i = 0; i < npeople; i++) {
      if (population[i].getstatus() == -1)
        count_rec++;
      else if (population[i].getstatus() == -2)
	count_inoc++;
      else if (population[i].getstatus() == 0)
	count_susc++;
      else if (population[i].getstatus() > 0 || population[i].getstatus() == -3)
	count_inf++;
    }
    cout << "In step " << setw(3) << step << ": " << 100.*count_inf/(float)npeople; 
    cout << " % are sick, " << 100.*count_susc/(float)npeople;
    cout << " % are susceptible, " << 100.*count_rec/(float)npeople;
    cout << " % have recovered, and " << 100.*count_inoc/(float)npeople;
    cout << " % are inoculated." << endl;
  };
  void open_file(ofstream &file_out) {  // open an output file
    file_out.open("disease.out");    
    file_out << "step  npeople infected  susceptible  recovered  vaccinated" << endl;
  };
  void wrt_file(ofstream &file_out, int step) {  // write an output file for each time step
    int count_inf = 0, count_inoc = 0, count_susc = 0, count_rec = 0, width = 15;
    for (int i = 0; i < npeople; i++) {  // first count all the parameters using one loop.
      if (population[i].getstatus() == -1)
        count_rec++;
      else if (population[i].getstatus() == -2)
	count_inoc++;
      else if (population[i].getstatus() == 0)
	count_susc++;
      else if (population[i].getstatus() > 0 || population[i].getstatus() == -3)
	count_inf++;
    }
    file_out << setw(width) << step << setw(width) << npeople << setw(width) << count_inf; // write them all
    file_out << setw(width) << count_susc << setw(width) << count_rec << setw(width) << count_inoc << endl;
  };
  void close_file(ofstream &file_out) {  // close the output file
    file_out.close();
  };
  void set_probability_of_transfer(float prob) {  // set the probability of disease transmission in the population.
    probability_of_transfer = prob;
  };
  void inoculate(float prob) {  // method to vaccinate randomly at the beginning.
    for (int i = 0; i < npeople; i++) {
      float good_luck = (float) rand()/(float)RAND_MAX;
      if (good_luck < prob)
        population[i].administer_vaccine();
    }  
  };
};
