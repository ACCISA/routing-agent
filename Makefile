all:
	docker build -t routing-agent .
	docker run -it routing-agent

.PHONY: all
