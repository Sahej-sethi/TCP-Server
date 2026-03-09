# High-Performance TCP Server (C++)

A professional-grade, multi-phase systems project focused on low-latency networking and Linux kernel internals. This project serves as a deep dive into the "Engine Room" of software engineering, moving from basic socket lifecycles to high-frequency trading (HFT) grade architectures.

## 👤 About the Author
* **Name:** Sahejreet Singh Sethi
* **Institution:** International Institute of Information Technology (IIIT), Hyderabad

## 🎯 Current Status: Phase 4 (Non-Blocking I/O) - *In Progress*
Having mastered synchronized multithreading with a Thread Pool in Phase 3, the project is now transitioning to **Event-Driven Architecture**. The goal is to utilize Linux `epoll` to handle thousands of concurrent connections on a single thread by moving away from blocking I/O calls.

### Phase 3 Technical Achievements:
* **Static Thread Pooling:** Eliminated the overhead of per-connection thread creation by "pre-hiring" a fixed set of worker threads.
* **Synchronized Task Queuing:** Implemented a thread-safe `std::queue` protected by `std::mutex` to manage incoming client file descriptors.
* **OS-Level Signaling:** Utilized `std::condition_variable` to put worker threads into a low-power "Deep Sleep" state, waking them only via kernel-level signals (`notify_one`) when tasks arrive.
* **RAII Lock Management:** Employed `std::lock_guard` and `std::unique_lock` to ensure exception-safe mutex handling and prevent deadlocks.

## 📊 Performance Benchmarks (Phase 3)
Stress-tested the Thread Pool implementation on Fedora Linux using ApacheBench (`ab -n 10000 -c 100`).



* **Throughput:** `5,876.23` Requests Per Second (RPS)
* **Reliability:** 0 Failed Requests (100% success rate under heavy load)
* **Tail Latency (P99):** `19 ms`
* **Latency Consistency:** Standard Deviation of only `2.3 ms`, proving the architecture is highly predictable—a key requirement for HFT systems.

*Note: While raw RPS is lower than Phase 2 due to lock contention on the global queue, the system is significantly more stable and resource-efficient under extreme concurrency.*

## 🛠️ Project Roadmap
- [x] **Phase 1: Synchronous Foundation** - Single-threaded blocking I/O.
- [x] **Phase 2: Naive Multithreading** - "Hire & Fire" detached threads.
- [x] **Phase 3: Thread Pooling** - Fixed-size worker pool with `mutex` and `condition_variable`.
- [ ] **Phase 4: Non-Blocking I/O (`epoll`)** *(Current Focus)*
    - Moving toward an event-driven architecture using Linux `epoll` for maximum scalability.
- [ ] **Phase 5: Performance Tuning**
    - Exploring zero-copy optimizations (sendfile), lock-free queues, and CPU pinning.

## 🚀 Setup & Run
1. **Compile (Optimized):** `g++ -O3 server.cpp -o server -pthread`
2. **Run:** `./server`
3. **Benchmark:** `ab -n 10000 -c 100 http://localhost:8080/`