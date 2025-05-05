# 🧠 philo — The Dining Philosophers Problem in C (Multithreading)


A concurrent programming project to simulate the classical Dining Philosophers Problem using **POSIX threads (pthreads)** and **mutexes** to prevent data races and ensure safe resource sharing.

## 🪑 Project Summary

This project is a part of the 42 School curriculum. It focuses on implementing a low-level thread-based simulation where multiple philosophers (threads) compete for shared resources (forks), requiring careful synchronization.

---

## 🧠 Problem Description

- N philosophers sit at a round table with N forks (1 between each philosopher).
- A philosopher must pick up **both left and right forks** to eat.
- After eating, they sleep, then think, then repeat.
- If a philosopher doesn’t eat within `time_to_die`, they die.
- The simulation ends either when one dies or all eat enough times.

---

## 💡 Implementation Highlights

- Each philosopher is implemented as a **POSIX thread**.
- Each fork is protected by a **mutex** to avoid data races.
- Custom time tracking via `gettimeofday()` for millisecond precision.
- All logging is synchronized to avoid interleaved console output.
- Proper memory management and clean thread termination.

---

## 🔧 Build and Run

### ⚙️ Compile

```bash
cd philo
make
```
### 🚀 Run

  ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

### Example
```bash
  ./philo 5 800 200 200
```
### 🔒 Race Condition Prevention

To prevent race conditions:

   Each fork is represented as a pthread_mutex_t.
   Access to forks is protected with pthread_mutex_lock/unlock.
   Logging is serialized via a print-lock mutex.
   The simulation checks death conditions using timestamp comparison in millisecond resolution.

### 🧵 Thread Lifecycle Overview

Each philosopher thread follows this loop:

  Take left fork
  Take right fork
  Eat
  Release forks
  Sleep
  Think
  Repeat (or die)

### 📸 Screenshot

![image](https://github.com/user-attachments/assets/d53a5caa-ef6a-4aba-a9c6-e53c60676381)

### 📚 What I Learned
  Practical use of POSIX threads and mutex synchronization
  Designing systems with no global variables or race conditions
  Handling timed events with precision (gettimeofday + usleep)
  Writing deterministic simulations using low-level tools

### 🛠️ Tech Stack
- Tool	Purpose
- C	Core implementation
- pthread	Thread creation and synchronization
- Makefile	Build automation
- gettimeofday	Millisecond-level timestamping
- usleep	Precision sleeping for simulating durations
### 🔮 Future Improvements
   Rewrite using processes + semaphores (philo_bonus)
   Visual output (e.g., SDL or ncurses)
   Advanced detection: starvation probability, deadlock prevention strategies

   Add stress test CLI options

📄 License

This project is part of the 42 School curriculum and is distributed for educational purposes only.
