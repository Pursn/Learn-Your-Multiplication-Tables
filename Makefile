project:
	#Remember that "-lm" links the math library to "main.c"
	gcc main.c -o lymt -lm
clean:
	rm -rf lymt
	rm -rf lymt.conf
run:
	./lymt
test:
	gdb ./lymt
