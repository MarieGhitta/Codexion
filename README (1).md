*This project has been created as part of the 42 curriculum by mghitta.*

# Codexion

## Description

Codexion is a concurrency and synchronization project inspired by the classic Dining Philosophers problem.  
The goal is to simulate multiple coders competing for limited shared resources (USB dongles) while avoiding:

- deadlocks
- starvation
- race conditions
- inaccurate timeout detection

Each coder is represented by a POSIX thread and alternates between:

1. compiling
2. debugging
3. refactoring

To compile, a coder must acquire **two dongles simultaneously**.  
The simulation ends when:

- one coder burns out (fails to compile before `time_to_burnout`)
- or every coder has compiled `number_of_compiles_required` times.

The project focuses heavily on:

- multithreading
- mutex synchronization
- condition variables
- scheduling algorithms
- timing precision
- thread-safe communication

---

# Features

- Multi-threaded simulation using `pthread`
- FIFO and EDF scheduling policies
- Custom priority queue (heap implementation)
- Dedicated monitor thread for burnout detection
- Serialized logging with mutex protection
- Dongle cooldown system
- Thread-safe shared state management
- Input parsing and validation
- Single coder edge-case handling
- Clean memory deallocation

---

# Instructions

## Compilation

```bash
make
```

The project is compiled with:

```bash
-Wall -Wextra -Werror -pthread
```

---

## Execution

```bash
./codexion number_of_coders time_to_burnout time_to_compile \
time_to_debug time_to_refactor \
number_of_compiles_required dongle_cooldown scheduler
```

### Arguments

| Argument | Description |
|---|---|
| `number_of_coders` | Number of coder threads and dongles |
| `time_to_burnout` | Max time before a coder burns out |
| `time_to_compile` | Time spent compiling |
| `time_to_debug` | Time spent debugging |
| `time_to_refactor` | Time spent refactoring |
| `number_of_compiles_required` | Simulation stops once all coders reach this amount |
| `dongle_cooldown` | Cooldown before a dongle becomes reusable |
| `scheduler` | `fifo` or `edf` |

---

## Example

```bash
./codexion 5 800 200 200 200 5 50 fifo
```

---

# Project Architecture

## Main Components

### `codexion.c`

Program entry point:

- argument validation
- simulation initialization
- heap initialization
- thread creation
- cleanup and destruction

---

### `simulation.c`

Responsible for:

- allocating coders and dongles
- initializing mutexes
- initializing condition variables
- assigning left/right dongles
- global simulation setup

---

### `threads.c`

Creates and joins:

- coder threads
- scheduler thread
- monitor thread

---

### `routine.c`

Contains the main coder routine.

Each coder repeatedly:

1. requests compilation access
2. waits for scheduler permission
3. compiles
4. debugs
5. refactors

Special handling is implemented for the single coder case.

---

### `scheduler.c`

Implements the scheduling system.

The scheduler thread:

- pops requests from the heap
- checks dongle availability
- grants access according to:
  - FIFO
  - EDF (Earliest Deadline First)

---

### `heap.c` / `heap_utils.c`

Custom priority queue implementation.

Used to arbitrate coder requests safely and efficiently.

The EDF implementation prioritizes coders with the earliest burnout deadline:

```text
deadline = last_compile_start + time_to_burnout
```

---

### `monitor.c`

Dedicated monitor thread.

Responsibilities:

- detecting burnout precisely
- stopping the simulation
- checking compile completion conditions

---

### `logging.c`

Ensures serialized logging with a mutex to prevent interleaved output.

---

### `time.c`

Provides:

- millisecond timestamps
- simulation-relative timing
- smart sleeping loop

---

# Blocking Cases Handled

## 1. Deadlock Prevention

The implementation avoids classic deadlock situations by introducing a centralized scheduler thread.

Instead of allowing coders to independently lock dongles in arbitrary order, all compile requests pass through the scheduler and heap system.

This removes circular waiting conditions and prevents multiple coders from holding partial resources simultaneously.

---

## 2. Starvation Prevention

Two scheduling strategies are implemented:

### FIFO

Requests are processed in arrival order.

### EDF (Earliest Deadline First)

Requests are prioritized according to:

```text
last_compile_start + time_to_burnout
```

This helps prioritize coders closest to burnout.

---

## 3. Dongle Cooldown Handling

Each dongle stores:

- `is_taken`
- `last_release_time`

After release, a dongle becomes temporarily unavailable until:

```text
current_time - last_release_time >= dongle_cooldown
```

This logic is checked before granting access.

---

## 4. Precise Burnout Detection

A dedicated monitor thread continuously checks all coders.

Burnout occurs when:

```text
current_time - last_compile_start >= time_to_burnout
```

The monitor immediately logs the burnout event and stops the simulation.

---

## 5. Serialized Logging

All output passes through a dedicated writing mutex:

```c
pthread_mutex_lock(&sim->writing);
```

This guarantees that no two logs are mixed together.

---

# Thread Synchronization Mechanisms

## Mutexes (`pthread_mutex_t`)

The project uses several mutexes to protect shared resources.

### Dongle Mutexes

Each dongle has its own mutex:

```c
pthread_mutex_t lock_dongle;
```

Used to protect:

- dongle ownership
- cooldown timestamps
- availability state

---

### Writing Mutex

Protects terminal output.

Prevents concurrent `printf` calls from interleaving.

---

### Stop Simulation Mutex

Protects the global stop flag:

```c
sim->stop_sim
```

Used by all threads to safely terminate execution.

---

### Heap Mutex

Protects access to the shared request heap:

- push operations
- pop operations
- scheduling arbitration

---

### Per-Coder Mutexes

Each coder has dedicated mutexes for:

- compile count
- last compile timestamp
- waiting state

This prevents race conditions between:

- coder threads
- scheduler thread
- monitor thread

---

## Condition Variables (`pthread_cond_t`)

Each coder owns a condition variable:

```c
pthread_cond_t wait;
```

Coders block while waiting for scheduler authorization:

```c
pthread_cond_wait(...)
```

The scheduler signals the coder once both dongles become available.

This avoids active busy-waiting and reduces CPU usage.

---

## Thread-safe Communication

Communication between threads happens through:

- protected shared variables
- condition variables
- mutex synchronization

Examples:

- scheduler grants compile permission
- monitor stops all threads safely
- coders notify simulation completion

---

# Technical Choices

## Why a Scheduler Thread?

Using a dedicated scheduler simplified synchronization logic significantly.

Benefits:

- prevents deadlocks
- centralizes arbitration
- supports multiple scheduling algorithms
- simplifies fairness management

---

## Why a Heap?

A heap provides efficient priority management:

- `O(log n)` insertion
- `O(log n)` extraction

This is especially useful for EDF scheduling.

---

## Timing Strategy

The project uses:

```c
gettimeofday()
```

to measure time in milliseconds.

A custom `smart_sleep()` loop improves timing precision by checking simulation state frequently.

---

# Resources

## Documentation

- POSIX Threads Documentation  
  https://man7.org/linux/man-pages/man7/pthreads.7.html

- Mutex Documentation  
  https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html

- Condition Variables  
  https://man7.org/linux/man-pages/man3/pthread_cond_wait.3p.html

- gettimeofday Documentation  
  https://man7.org/linux/man-pages/man2/gettimeofday.2.html

---

## Articles & References

- Dining Philosophers Problem  
  https://en.wikipedia.org/wiki/Dining_philosophers_problem

- EDF Scheduling  
  https://en.wikipedia.org/wiki/Earliest_deadline_first_scheduling

- Heap / Priority Queue  
  https://www.geeksforgeeks.org/priority-queue-using-binary-heap/

---

## AI Usage

AI tools were used primarily for:

- explaining synchronization concepts
- reviewing concurrency strategies
- improving README structure
- verifying theoretical concepts around deadlocks and EDF scheduling

All implementation logic, debugging, testing, and final code integration were reviewed and understood manually.

---

# Compliance Check

## Requirements Successfully Implemented

- POSIX threads
- mutex protection
- monitor thread
- scheduler thread
- FIFO / EDF arbitration
- custom heap implementation
- serialized logging
- input validation
- single coder handling
- dongle cooldown
- simulation stop conditions

---

## Important Issues To Fix Before Evaluation

### 1. Critical Bug in `release_dongle()`

The function unlocks dongle mutexes twice:

```c
pthread_mutex_unlock(&coder->right_dongle->lock_dongle);
pthread_mutex_unlock(&coder->left_dongle->lock_dongle);
```

after they were already unlocked earlier.

This can cause undefined behavior and must be fixed immediately.

---

### 2. Potential Data Race in `grant_dongles()`

Inside `scheduler.c`, the scheduler modifies:

```c
left_dongle->is_taken
right_dongle->is_taken
```

without locking the dongle mutexes.

This may trigger ThreadSanitizer warnings and should be protected with the corresponding mutexes.

---

### 3. Makefile Concern

The subject requires compilation with:

```bash
-Wall -Wextra -Werror -pthread
```

Your Makefile additionally enables:

```bash
-fsanitize=thread
```

This is excellent for debugging, but for final submission it is safer to remove it unless explicitly allowed by your school.

---

### 4. EDF Tie-breaker

The subject mentions deterministic tie-breaking for equal EDF deadlines.

Your current heap comparison does not appear to fully handle equal deadlines explicitly.

Adding FIFO arrival order as a secondary comparison would improve determinism.

---

# Final Notes

This project demonstrates strong understanding of:

- multithreading
- synchronization
- scheduling
- race condition prevention
- timing-sensitive programming

The overall architecture is clean and modular, especially the separation between:

- scheduler
- monitor
- coder routines
- heap management

After fixing the identified synchronization issues, the project should be in a very solid state for evaluation.
