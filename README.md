Overview
This C program is an implementation of the classic Dining Philosophers Problem using threads and semaphores. The problem illustrates synchronization and resource sharing issues between multiple processes or threads, represented by philosophers sitting at a table who alternate between thinking, becoming hungry, and eating. Each philosopher requires two forks (represented as shared resources) to eat, and the challenge is to ensure that no deadlock or starvation occurs as they compete for these forks.

Key Components
Constants and Definitions
N: The number of philosophers (5 in this case).
LEFT and RIGHT: Macros that determine the left and right neighbors of a philosopher.
THINKING, HUNGRY, and EATING: States that represent whether a philosopher is thinking, hungry, or eating.
Shared Variables
state[N]: An array representing the current state (THINKING, HUNGRY, or EATING) of each philosopher.
number[N]: An array holding the IDs of the philosophers.
sem_t mutex: A semaphore that acts as a mutex to protect shared variables from race conditions.
sem_t s[N]: An array of semaphores, one for each philosopher, to signal when they can start eating.
Functions
test(int phil):

This function checks whether a philosopher phil can start eating. A philosopher can eat if they are hungry and neither of their neighbors is eating. If the conditions are met, the philosopher's state is set to EATING, and they are allowed to eat.
take_forks(int phil):

When a philosopher becomes hungry, they call this function to try to take the two forks they need to eat. The function waits for the mutex to gain access to the shared variables, updates the philosopher's state to HUNGRY, and then calls the test() function to check if they can start eating.
put_fork(int phil):

After finishing their meal, a philosopher calls this function to put down their forks. The function sets the philosopher's state to THINKING and checks whether their neighbors can now start eating.
*philosopher(void phil)**:

This is the function executed by each philosopher thread. Philosophers alternate between thinking and trying to eat. When a philosopher is ready to eat, they call take_forks() to grab the forks, and after eating, they call put_fork() to release them.
Main Function
sem_init(): Initializes the semaphores, both for the mutex and for each philosopher.
pthread_create(): Creates one thread for each philosopher, running the philosopher() function.
pthread_join(): Waits for each philosopher thread to finish.
Key Behavior
Philosophers will repeatedly alternate between thinking and attempting to eat.
The use of semaphores ensures that philosophers do not grab forks simultaneously in a way that would cause deadlock. Each philosopher waits for their turn to eat if either of their neighbors is eating.
The program controls access to shared variables with the mutex semaphore, preventing race conditions when philosophers check and update their states.
Notes
The program prevents deadlock by ensuring that a philosopher can only start eating if both neighboring philosophers are not eating.
sleep() calls are used to simulate the passage of time during the eating and thinking processes.
