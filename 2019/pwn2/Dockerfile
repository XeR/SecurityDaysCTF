FROM alpine

ADD     app/* /home/challenge/
WORKDIR /home/challenge

# Build challenge
RUN apk update
RUN apk add gcc make libc-dev && make && apk del gcc make libc-dev

# Add socat
RUN apk add socat

# Change rights
RUN chown root:root -R /home/challenge         \
	&& chmod o=   /home/challenge -R       \
	&& chmod o=x  /home/challenge          \
	&& chmod o=r  /home/challenge/flag     \
	&& chmod o=r  /home/challenge/Makefile \
	&& chmod o=r  /home/challenge/main.c   \
	&& chmod o=rx /home/challenge/main     \
	&& chmod o=rx /home/challenge/run.sh

# Add user
RUN adduser -D -H challenge

# Run
USER challenge
CMD ["/home/challenge/run.sh"]
