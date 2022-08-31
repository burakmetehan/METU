the3:
	gcc the3.c -ansi -Wall -pedantic-errors -o the3
test:
	gcc testing.c the3.c input_taker.c -ansi -Wall -pedantic-errors -o test && ./test < in
rm:
	rm test
retest:
	rm test && gcc testing.c the3.c input_taker.c -ansi -Wall -pedantic-errors -o test && ./test < in > out
temp:
	gcc temp.c -ansi -Wall -pedantic-errors -o temp && ./temp
retemp:
	rm temp && gcc temp.c -ansi -Wall -pedantic-errors -o temp && ./temp
input_taker:
	gcc input_taker.c -ansi -Wall -pedantic-errors -o input_taker && ./input_taker < input > output
reinput_taker:
	rm input_taker && gcc input_taker.c -ansi -Wall -pedantic-errors -o input_taker && ./input_taker < input > output