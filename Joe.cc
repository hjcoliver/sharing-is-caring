// A code to study how a single individual gets sick and recovers.
#include "begin.h"
#include "Person.h"

int main() {
  srand( (unsigned)time( NULL ) );  // seed the random number generator. 
  Person joe(0);  // define joe, our guinea pig.

  for ( int step = 1; ; step++ ) {  // loop over time
    joe.update();  // update Joe's status.
    float bad_luck = (float) rand()/(float)RAND_MAX; // get a random number
    if (bad_luck>.95)  // if random number is bigger than disease threshold, Joe gets sick
      joe.infect(5);  // and Joe is ill for 5 days
    
    cout << "On day " << step << ", Joe is "  // print to screen Joe's status
         << joe.status_string_sing() << endl;
    if (joe.is_stable())  // if Joe has healed
        break;
  }
  return 0;   //Finished!
}
