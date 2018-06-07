all:
	gcc src/part1.c -o part1
test:	
	gcc src/main.c src/part2.c src/part3.c -o part2
clean:
	rm part1
	rm part2
	rm part3