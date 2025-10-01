# Mini Redis

A lightweight Redis-like system implemented in C++.
This project allows you to store key-value pairs in memory while ensuring data persistence across restarts.
Persistence is achieved by storing the data in a .json file. When the server restarts, the contents of this JSON snapshot are automatically loaded back into memory.

# Features

In-memory key-value store – Fast operations like SET, GET, and DEL.
Persistence with JSON snapshots – Data is saved to a JSON file so that nothing is lost when the server restarts.
Concurrency support – Multiple clients can connect and interact with the server at the same time.
Custom command parser – Simple text-based protocol to send commands.

# Commands Supported

SET key value → Store a key-value pair.
GET key → Retrieve the value of a key.
DEL key → Delete a key from the store.
SAVE → Force save the current state to the JSON snapshot file.
EXIT → Disconnect client from the server.

# How to Run
1. Build the server
g++ parser.cpp json_store.cpp server.cpp -o server -pthread
2. Build the client
g++ client.cpp -o client
3. Run the server
./server
4. Run the client
./client
You can start multiple clients to connect concurrently to the server.

# Project Structure
mini_redis/
1. server.cpp       # Server code (handles client connections)
2. client.cpp       # Client code (connects to server)
3. parser.cpp       # Command parser
4. json_store.cpp   # JSON snapshot handling (load/save)
5. json_store.h     # Header for db + mutex
6. snapshot_db.json # Persistent database (auto-created)

# Future Improvements

Append Only File (AOF) persistence mode.
More Redis-like commands (e.g., EXISTS, FLUSHDB).
Authentication support.
Performance optimizations.

This project is a learning-oriented mini version of Redis, showcasing how databases can be designed with persistence + concurrency.

