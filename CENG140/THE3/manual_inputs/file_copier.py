import os

copy_count = int(input("Copy Count: "))
function_code = int(input("Function Code: "))

for i in range(copy_count):
	os.system(f"cp ./case ./function_{function_code}/case{i+1}")
