project:
	gcc main.c -o lymt -lm
clean:
	rm -rf lymt
run:
	./lymt
test:
	gdb ./lymt
