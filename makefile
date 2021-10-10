all:HW1_1.c HW1_2.c
	gcc -o HW1_1 HW1_1_R.c
	gcc -o HW1_2 HW1_2_R.c
clean:
	rm -rf HW1_1 HW1_2
