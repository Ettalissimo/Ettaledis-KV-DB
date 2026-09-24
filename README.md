Ettaledis Redis lite clone : My way to learn Redis

Road map to follow

### In-memory hash map + TCP server

Build the core std::unordered_map store guarded by a single mutex, and a basic TCP server (POSIX sockets or epoll) that accepts connections and parses a simple line-based protocol: SET key value, GET key, DEL key. No concurrency optimization yet — just get client-to-store round trips working end to end.

On day 1: create the store class which wraps up a hash map we have methods (set, get, update )


┌──────────────────────────────────────┐
│         Your server process          │
│                                      │
│   Store store;   ← one instance,     │
│                     lives in memory  │
│         ↑                            │
│         │ calls store.set() / .get() │
│         │                            │
│   TCP server loop:                   │
│     accept() a client connection     │
│     read bytes → "SET foo bar"       │
│     parse into command + args        │
│     call store.set("foo", "bar")     │
│     write response back → "OK"       │
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

Documentation for c++ networking :

https://beej.us/guide/bgnet/html/#system-calls-or-bust


https://www.geeksforgeeks.org/cpp/socket-programming-in-cpp/

client sends request to server via sockets 
this request is then passed to a mini compiler

every string is tokenized 
we dispatch each line at a key word like set get del
we consider that a full command 
then check every command if it matches the number of argument needed
if all good call the store methods


tokenize → check keyword → check arity → dispatch

The language Rules :

SET key value → keyword + 2 more tokens (key, value) → arity 2
GET key       → keyword + 1 more token (key) → arity 1
DEL key       → keyword + 1 more token (key) → arity 1


To run code using CMake:
`mkdir build && cd build
cmake ..
make`


in build/

`./server
./client`

After adding new files later

Just add the new .cpp to the relevant list in CMakeLists.txt (e.g. a new src/expiry.cpp goes into COMMON_SOURCES if both need it, or directly into add_executable(server ...) if it's server-only), then re-run:

`cmake ..
make`