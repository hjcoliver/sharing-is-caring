class Person {  // define the class for a person
 private:
  int status;  // Define member ID number.
 public:
  Person() {};
 Person( int status ) : status(status) {};
  int getstatus() { return status; };  // return the status of the person
  string status_string_sing() {  // return string corresponding to status of single person
    if (status == 0) { return "susceptible"; }
    else if (status == -1) { return "recovered"; }
    else if (status == -2) { return "inocculated"; }
    else if (status > 0) { return "sick (" + to_string(status) + " to go)";} 
  };
  string status_string() {  // return string corresponding to status of person
    if (status == 0) { return "?"; }  // susceptible
    else if (status == -1) { return "-"; }  // recovered
    else if (status == -2) { return "-"; }  // inocculated
    else if (status == -3) { return "+"; }  // just infected
    else if (status > 0) { return "+" ;}   // sick
  }; 
  void update() {  // update the Person's status with the new step
    if (status > 1) { status--; }  // if sick, reduce days left sick
    else if (status == 1) { status = -1; }  // heal them
  };
  void infect(int n) { status = n; };  // infect with n days long sickness
  bool is_stable() {  // return if sick or not
    if (status < 0) { return true; }
    else { return false; } 
  };
  void administer_vaccine() { status = -2; };  // person becomes innoculated
};
