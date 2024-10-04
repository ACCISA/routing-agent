# routing-agent
simple agent to route tcp and perform a task
\n
this agent runs on a single thread and utilizes a reactor pattern to poll fd for state changes. Tasks and reactor jobs are queued and ran in a loop. \n
messages are encrypted using AES. Each agent has its own key that the console uses to encrypt and decrypt messages. \n
comms between agent uses tls. \n
step: write server.c
step: implement SSL
step: implement reactor pattern


