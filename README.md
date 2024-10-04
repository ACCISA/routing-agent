# routing-agent
simple agent to route tcp and perform a task
this agent runs on a single thread and utilizes a reactor pattern to poll fd for state changes. Tasks and reactor jobs are queued and ran in a loop.
messages are encrypted using AES. Each agent has its own key that the console uses to encrypt and decrypt messages.
comms between agent uses tls.
step: write server.c
step: implement SSL
step: implement reactor pattern


