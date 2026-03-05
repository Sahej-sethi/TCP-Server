# High-Performance TCP Server (C++)

A professional-grade, multi-phase systems project focused on low-latency networking and Linux kernel internals. This project serves as a deep dive into the "Engine Room" of software engineering, moving from basic socket lifecycles to high-concurrency architectures.

## 👤 About the Author
* **Name:** Sahejreet Singh Sethi
* **Institution:** International Institute of Information Technology (IIIT), Hyderabad

## 🎯 Current Status: Phase 1 (Foundation)
This baseline phase establishes a robust Synchronous TCP foundation. It successfully handles the core 3-way handshake and serves raw HTTP/1.1 frames to modern web browsers.

### Technical Achievements:
* **Socket Management:** Handled the complete `socket -> bind -> listen -> accept` lifecycle using the Linux Socket API.
* **Endianness Awareness:** Implemented `htons()` and `ntohs()` to ensure network-byte-order transparency (Big-Endian vs. Little-Endian).
* **Protocol Engineering:** Engineered manual HTTP/1.1 response framing with correct CRLF (`\r\n`) separators.
* **Build Automation:** Configured a `Makefile` with `-O3` optimization and strict warning flags (`-Wall`) for production-grade compilation.

## 🛠️ Project Roadmap
This project is an evolving system. I am building it in deliberate stages to master the transition from simple I/O to high-frequency trading (HFT) grade performance:

- [x] **Phase 1: Synchronous Foundation** (Current)
    - Single-threaded blocking I/O; basic HTTP handling.
- [ ] **Phase 2: Naive Multithreading** (Upcoming - Post Mid-Sem)
    - Spawning a new thread per connection to handle multiple concurrent clients.
- [ ] **Phase 3: Thread Pooling**
    - Implementing a fixed-size worker pool with a task queue to eliminate thread-creation overhead.
- [ ] **Phase 4: Non-Blocking I/O (`epoll`)**
    - Moving toward an event-driven architecture using Linux `epoll` for massive scalability.
- [ ] **Phase 5: Performance Tuning**
    - Exploring zero-copy optimizations, lock-free data structures, and CPU pinning.

## 🚀 Setup & Run
1. Compile: `make`
2. Run: `./server`
3. Test: Open `localhost:8080` in your browser.
