This is a 42 school project to learn about multithreading in C.

## Task Description

The goal of this project is to simulate the classic "Dining Philosophers Problem," a well-known problem in computer science that illustrates synchronization issues in concurrent programming. Philosophers sit around a table with a fork between each pair. Each philosopher alternates between eating, thinking, and sleeping. To eat, a philosopher must pick up both forks adjacent to them. The challenge is to ensure that no philosopher starves while avoiding deadlocks and race conditions.

The program must:
- Create a specified number of philosopher threads.
- Use mutexes to manage access to shared resources (forks and print statements).
- Monitor the state of each philosopher to ensure they do not starve.
- Stop the simulation immediately if a philosopher dies or if all philosophers have eaten a specified number of times.

## Usage

```
cd philo
make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat] # last argument is optional
```

### Arguments:
1. `number_of_philosophers`: The number of philosophers (and forks) at the table.
2. `time_to_die`: Time in milliseconds a philosopher can live without eating.
3. `time_to_eat`: Time in milliseconds it takes for a philosopher to eat.
4. `time_to_sleep`: Time in milliseconds a philosopher spends sleeping.
5. `[number_of_times_each_philosopher_must_eat]` (optional): If provided, the simulation ends when all philosophers have eaten this many times.

### Example:
```
./philo 5 800 200 200 3
```
This starts a simulation with 5 philosophers, where each philosopher has 800ms to eat before dying, takes 200ms to eat, 200ms to sleep, and the simulation ends after each philosopher has eaten 3 times.

## Concepts Learned

This project provided me with hands-on experience with:
- **Multithreading**: Creating and managing threads using the `pthread` library.
- **Mutexes**: Ensuring atomic access to shared resources to prevent race conditions.
- **Deadlock Prevention**: Implementing strategies to avoid deadlocks when philosophers compete for forks.
- **Thread Synchronization**: Using mutexes and condition variables to coordinate thread behavior.
- **Time Management**: Measuring and managing time in milliseconds using `gettimeofday` and `usleep`.
- **Simulation Design**: Designing a system where multiple entities (philosophers) interact with shared resources (forks) under strict rules.
- **Error Handling**: Managing errors in thread creation, mutex initialization, and argument parsing.
- **Memory Management**: Allocating and freeing resources dynamically to ensure no memory leaks.
- **Concurrency Challenges**: Understanding and solving issues like starvation, livelocks, and race conditions.
- **Code Modularity**: Structuring the program into reusable and maintainable components.

## Key Features

- **Thread-safe Logging**: Ensures that print statements do not interleave, even when multiple threads attempt to log simultaneously.
- **Dynamic Configuration**: Allows the number of philosophers and other parameters to be specified at runtime.
- **Graceful Termination**: Stops the simulation immediately when a philosopher dies or the eating condition is met.
- **Scalability**: Supports up to 1000 philosophers, with performance optimized for large numbers of threads.

## Notes

- The program assumes that all times (to die, eat, and sleep) are provided in milliseconds and are greater than or equal to 10ms.
- Philosophers are numbered starting from 1.
- If only one philosopher is present, they will starve since they cannot pick up two forks.
