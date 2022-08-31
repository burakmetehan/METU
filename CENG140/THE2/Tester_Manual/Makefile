creator:
	gcc tester_creator.c functions.c print_functions.c -ansi -Wall -pedantic-errors -o tester_creator
clean_creator:
	rm tester_creator
clean_output:
	rm tester_creator_output tester_result
clean:
	rm tester_creator tester_creator_output tester_result
run:
	./tester_creator < tester_input > tester_creator_output
check:
	python3 tester.py > tester_result
