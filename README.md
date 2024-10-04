# TCP Routing Agent

A simple agent designed to route TCP connections and perform tasks. This agent runs on a single thread and uses the **reactor pattern** to monitor file descriptors for state changes. Tasks and reactor jobs are queued and executed within a loop, ensuring non-blocking operations.

## Features

- **Single-threaded Reactor Pattern**: 
  - Monitors and handles file descriptor events using a non-blocking, event-driven design.
- **AES Encryption**:
  - All messages are encrypted using AES. Each agent has a unique key for message encryption and decryption.
- **TLS Communication**:
  - Secure communication between agents using TLS (Transport Layer Security).
- **Custom Routing Protocol**:
  - Implements a custom protocol for routing messages between agents and delivering them to the intended destination efficiently.
- **Python Console Interaction**:
  - A Python console interface is provided for interacting with agents, allowing commands to be sent to agents, encrypted using AES, and routed via the custom protocol.

## Architecture

1. **Reactor Pattern**: 
   - The reactor monitors file descriptors and queues tasks for execution when events occur (e.g., read/write readiness).
   
2. **AES Encryption**: 
   - Messages sent between the console and agents are encrypted with AES using agent-specific keys.
   
3. **TLS for Communication**: 
   - All communication between agents is secured using TLS, ensuring encrypted and authenticated data transfer.

## How It Works

1. **Initialize the Agent**: 
   - Each agent starts a single-threaded loop that listens for incoming connections and queues jobs when events occur.
   
2. **Encrypt/Decrypt Messages**: 
   - The console sends encrypted messages to the agent using a shared AES key. The agent decrypts messages and processes them accordingly.
   
3. **Secure Communication**: 
   - All communication between agents is encrypted using TLS, ensuring the integrity and confidentiality of messages exchanged.

## Requirements

- OpenSSL (for TLS and AES encryption)
- GCC or any compatible C compiler
