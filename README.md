Ettaledis Redis lite clone : My way to learn Redis

Road map to follow

### In-memory hash map + TCP server

Build the core std::unordered_map store guarded by a single mutex, and a basic TCP server (POSIX sockets or epoll) that accepts connections and parses a simple line-based protocol: SET key value, GET key, DEL key. No concurrency optimization yet — just get client-to-store round trips working end to end.

