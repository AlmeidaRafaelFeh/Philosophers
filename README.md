*This project was created as part of the 42 curriculum by rafreire*

## Description

The Philosophers project is an introduction to concurrent programming and synchronization using POSIX threads (pthreads). The goal is to solve the classic Dining Philosophers problem while preventing deadlocks, race conditions, and starvation.

A major focus of this implementation was understanding how thread scheduling and timing behave in real-world execution. During development, I spent considerable time studying how sleep functions interact with mutex-protected sections and how small timing differences can drastically affect the simulation. This led to extensive experimentation with thread staggering, fork acquisition order, and synchronization strategies to better understand and control execution delays.

To improve simulation stability, I implemented a staggered thread start where philosophers begin their routines with different initial delays. Additional timing adjustments were introduced for specific edge cases, particularly when dealing with an odd number of philosophers. These delays helped reduce fork contention and allowed the simulation to remain accurate even under very strict timing constraints.

A significant part of the project involved testing multiple synchronization approaches and fine-tuning timing values to achieve acceptable millisecond precision. Many edge cases were analyzed, including configurations with very low `time_to_die` values, where even minor scheduling inconsistencies could cause unexpected philosopher deaths. Through extensive testing and iteration, I was able to reach a balance between performance, fairness, and timing accuracy.

The project also provided a deeper understanding of thread lifecycle management, mutex synchronization, shared resource protection, and the challenges of building reliable concurrent applications in C.

## Instructions

### Compilation

```bash
make
```

### Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters

* `number_of_philosophers`: Number of philosophers and forks in the simulation.
* `time_to_die`: Time in milliseconds a philosopher can survive without eating.
* `time_to_eat`: Time in milliseconds spent eating.
* `time_to_sleep`: Time in milliseconds spent sleeping.
* `number_of_times_each_philosopher_must_eat` (optional): Simulation ends when every philosopher has eaten at least this number of times.

### Implementation Details

* Each philosopher is represented by an independent thread.
* Forks are protected using mutexes to ensure safe access between threads.
* Thread execution is intentionally staggered using small startup delays to reduce contention for forks.
* Additional timing adjustments are applied in specific scenarios involving an odd number of philosophers to improve simulation stability and avoid starvation.
* Shared variables are synchronized to prevent race conditions and ensure consistent monitoring of philosopher states.
* The simulation continuously checks for philosopher death and completion conditions while maintaining accurate timing behavior.

### Example

```bash
./philo 5 800 200 200
```

This command starts a simulation with:

* 5 philosophers
* 800ms before starvation
* 200ms eating time
* 200ms sleeping time

The simulation ends when a philosopher dies or when all philosophers have eaten the required number of times (if specified).

## Resources

### Documentation & References

- [Understanding threads in C](https://medium.com/@akshatarhabib/understanding-threads-in-c-c9feb5e9372a) - Medium
*autor* Akshatarhabib

### AI Usage

AI tools (GitHub Copilot) were used in this project for:
- **Code architecture**: Assistance in planning the workflow desing.
- **Documentation**: Assistance in writing comments and this README
- **Debugging assistance**: Identifying potential issues and suggesting fixes
- **Research**: Quick lookups on system calls and library functions
- **Functionality**: Intensive study of how threads work and how I could use mutexes to add delay to philosophos.

--
## Authors

- **rafreire** - [42 Profile](https://profile.intra.42.fr/users/rafreire)

## License

This project is part of the 42 School curriculum. All rights reserved.
