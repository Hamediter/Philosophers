*This project has been created as part of the 42 curriculum by [aboutale].*

# 🍝 Philosophers - Dining, Thinking, and Sleeping

<p align="center">
  <img src="https://img.shields.io/badge/Score-100%2F100-success?style=for-the-badge&logo=42" alt="Score">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c" alt="C">
  <img src="https://img.shields.io/badge/Tech-Pthreads-orange?style=for-the-badge" alt="Pthreads">
</p>

## 📝 Description
**Philosophers** is a classic synchronization problem in computer science. The goal is to simulate a group of philosophers sitting at a round table, doing three things: eating, thinking, and sleeping. 

The challenge lies in managing limited resources (forks) among multiple threads (philosophers) without running into **deadlocks** or **data races**.

### Key Features
- **Multithreading:** Each philosopher is represented by a thread.
- **Resource Management:** Forks are protected by **mutexes** to ensure only one philosopher uses a fork at a time.
- **Strict Monitoring:** A dedicated monitoring system checks if a philosopher dies (starvation) and stops the simulation immediately.
- **Timestamp Accuracy:** Precise time management using `gettimeofday` to track actions in milliseconds.

---

## 🏗️ Infrastructure Overview
- **Threading Library:** Extensive use of `pthread_create`, `pthread_join`, `pthread_mutex_init`, etc.
- **Protection Logic:** Every shared variable (like the time of the last meal or the "dead" flag) is protected by a mutex to prevent **Data Races**.
- **Optimization:** Minimized mutex locking time to ensure the simulation runs smoothly without unnecessary lags.

---

## 🛠️ Project Description & Design Choices

### Design Choices
*   **Preventing Deadlocks:** I implemented a logic where philosophers pick up forks in a specific order (e.g., even/odd strategy or a slight delay) to ensure the simulation never freezes.
*   **Performance:** Instead of a heavy "check" loop that consumes too much CPU, the monitoring system is optimized to sleep briefly between checks.
*   **Precision:** All output messages are timestamped from the start of the simulation to ensure absolute traceability.

---

## 🚀 Instructions

### Prerequisites
- `gcc` or `clang`
- `make`

### Installation & Execution
1.  **Compile:**
    ```bash
    make
    ```
2.  **Run the simulation:**
    ```bash
    # Usage: ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat (optional)]
    ./philo 5 800 200 200
    ```

---

## 📚 Resources

### References
- [Dining Philosophers Problem (Wikipedia)](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Pthreads Tutorials](https://llnl.gov/computing/tutorials/pthreads/)

### AI Usage
AI was used for:
- **Debugging Race Conditions:** Using AI to help interpret `valgrind --tool=helgrind` outputs.
- **Optimization:** Discussing the efficiency of different "deadlock avoidance" strategies.
- **Documentation:** Organizing this README to emphasize thread safety.
