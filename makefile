countdown: include/countdown.h src/countdown.c src/main.c
	gcc -o bin/countdown -I./include/ -s -std=gnu99 -Wall -pedantic src/countdown.c src/main.c

clean: bin/countdown 
	rm -f bin/countdown
