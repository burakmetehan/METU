result_generator:
	gcc ./code/result_creator.c ./code/functions.c ./code/print_functions.c -o result_generator
test_case_generator:
	pyinstaller  --onefile -w test_case_generator.py && mv ./dist/test_case_generator ./test_case_generator && rm -rf __pycache__ build dist test_case_generator.spec
run:
	./test_case_generator
run_py:
	python3 test_case_generator.py