build: train.c queue.c tema1.c
	gcc tema1.c train.c queue.c -Wall -Werror -Wextra -std=c99 -o tema1

run:
	./tema1

clean:
	rm -f tema1 tema1.in tema1.out
