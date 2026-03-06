# High-Performance TCP Server (C++)

A professional-grade, multi-phase systems project focused on low-latency networking and Linux kernel internals. This project serves as a deep dive into the "Engine Room" of software engineering, moving from basic socket lifecycles to high-concurrency architectures.

## 👤 About the Author
* **Name:** Sahejreet Singh Sethi
* **Institution:** International Institute of Information Technology (IIIT), Hyderabad

## 🎯 Current Status: Phase 3 (Thread Pooling) - *In Progress*
Successfully transitioned from a blocking synchronous server to a highly concurrent Phase 2 "Hire & Fire" multithreaded architecture. Currently implementing a Phase 3 static Thread Pool to eliminate OS-level thread allocation overhead and prevent kernel thrashing under extreme load.

### Phase 2 Technical Achievements:
* **Parallel Execution:** Implemented true concurrency using POSIX threads via the C++11 `<thread>` library, allowing simultaneous client handling.
* **Resource Management:** Safely decoupled thread lifecycles from the main listener loop using `std::thread::detach()`, preventing memory leaks and `std::terminate` crashes.
* **High-Concurrency Benchmarking:** Validated parallel execution and latency under load using ApacheBench (`ab`) and parallel background `curl` processes.

## 📊 Performance Benchmarks (Phase 2)
Stress-tested the naive multithreading implementation on a Linux environment using ApacheBench (`ab -n 1000 -c 100`).
* **Throughput:** `7,338.70` Requests Per Second (RPS)
* **Concurrency Level:** 100 simultaneous parallel connections
* **Reliability:** 0 Failed Requests
* **Latency:** `0.136 ms` mean time per request (across all concurrent requests)

*Note: While Phase 2 achieves excellent throughput for moderate traffic, Phase 3 is being developed to handle massive concurrency spikes without exhausting OS thread limits.*

## 🛠️ Project Roadmap
- [x] **Phase 1: Synchronous Foundation** - Single-threaded blocking I/O; basic HTTP handling.
- [x] **Phase 2: Naive Multithreading ("Hire & Fire")** - Spawning a new detached thread per connection to achieve true parallel execution.
- [ ] **Phase 3: Thread Pooling** *(Current Focus)*
    - Implementing a fixed-size worker pool with `std::queue`, `std::mutex`, and `std::condition_variable` to safely manage high-throughput task queuing.
- [ ] **Phase 4: Non-Blocking I/O (`epoll`)**
    - Moving toward an event-driven architecture using Linux `epoll` for maximum scalability.
- [ ] **Phase 5: Performance Tuning**
    - Exploring zero-copy optimizations, lock-free data structures, and CPU pinning.

## 🚀 Setup & Run
1. Compile: `g++ server.cpp -o server -pthread`
2. Run: `./server`
3. Test: Open `localhost:8080` in your browser, or benchmark it yourself using `ab -n 1000 -c 100 http://localhost:8080/`