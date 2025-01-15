FROM gcc:latest


RUN apt-get update && apt-get install -y libssl-dev

COPY . .

WORKDIR src
RUN make

CMD ["./test_program"]


