## Ettaledis — Redis-lite clone

*My way to learn Redis*

## Roadmap to follow

### In-memory hash map + TCP server

Build the core `std::unordered_map` store guarded by a single mutex, and a basic TCP server (POSIX sockets or epoll) that accepts connections and parses a simple line-based protocol: `SET key value`, `GET key`, `DEL key`. No concurrency optimization yet — just get client-to-store round trips working end to end.

On day 1: create the store class which wraps up a hash map. Methods: `set`, `get`, `del`.

```
┌──────────────────────────────────────┐
│         Your server process           │
│                                        │
│   Store store;   ← one instance,      │
│                     lives in memory   │
│         ↑                             │
│         │ calls store.set() / .get()  │
│         │                             │
│   TCP server loop:                    │
│     accept() a client connection      │
│     read bytes → "SET foo bar"        │
│     parse into command + args         │
│     call store.set("foo", "bar")      │
│     write response back → "OK"        │
└──────────────────────────────────────┘
              ↑ TCP connection
              │
   ┌──────────┴─────────────┐
   │   Client (anyone)      │
   │  - telnet, for testing │
   │  - a CLI you write     │
   │  - later: your Go      │
   │    ingestion service   │
   └────────────────────────┘
```

### Documentation for C++ networking

- https://beej.us/guide/bgnet/html/#system-calls-or-bust
- https://www.geeksforgeeks.org/cpp/socket-programming-in-cpp/

### Request handling

Client sends a request to the server via sockets. This request is then passed to a mini "compiler":

1. Tokenize the string
2. Dispatch on the first token (keyword: `set`, `get`, `del`)
3. Check the command matches the expected number of arguments (arity)
4. If valid, call the matching `Store` method

```
tokenize → check keyword → check arity → dispatch
```

### The language rules

```
SET key value → keyword + 2 more tokens (key, value) → arity 2
GET key       → keyword + 1 more token (key)          → arity 1
DEL key       → keyword + 1 more token (key)           → arity 1
exit
```

### Build (CMake)

```bash
mkdir build && cd build
cmake ..
make
```

Run from `build/`:

```bash
./server
./client
```

### Adding new files later

Add the new `.cpp` to the relevant list in `CMakeLists.txt` (e.g. a new `src/expiry.cpp` goes into `COMMON_SOURCES` if both need it, or directly into `add_executable(server ...)` if it's server-only), then re-run:

```bash
cmake ..
make
```

### First phase

Client can only send one request per connection.

### Second phase

Single connect → single request/response cycle → close.

Algo for supporting multiple req/res with one client:

```cpp
while (true) {                          // outer: accept new clients
    accept a client
    while (true) {                      // inner: handle many requests from THIS client
        recv() from client
        if (bytes_received == 0) break; // client disconnected
        process command(s), send response(s)
    }
    close(client_fd);                   // only close once inner loop ends
}
```