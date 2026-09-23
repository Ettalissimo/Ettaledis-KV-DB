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