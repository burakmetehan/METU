test:
	gcc functions_test.c functions.c print_functions.c -ansi -Wall -pedantic-errors -o function_test
clean_test:
	rm function_test
clean_output:
	rm function_test_check_result function_test_output_calls
run:
	./function_test < function_test_input > function_test_output_calls
check:
	python3 function_test_check.py > function_test_check_result
