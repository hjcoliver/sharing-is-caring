import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('disease.out', skiprows = 1)
step = data[:,0]
npeople = data[0,1]
infected = data[:,2]
susceptible = data[:,3]
recovered = data[:,4]
vaccinated = data[:,5]

plt.plot(step, infected/npeople, 'r')
plt.plot(step, susceptible/npeople, 'b')
plt.plot(step, recovered/npeople, 'g')
plt.plot(step, vaccinated/npeople, 'k')
plt.xlabel('Time step', fontsize = 16)
plt.ylabel('Proportion of population', fontsize = 16)
plt.tick_params(labelsize=16)
plt.legend(('Infected','Susceptible','Recovered','Vaccinated'), fontsize=12, loc='best')
plt.tight_layout()
plt.show()
