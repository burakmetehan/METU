

with open("eval.out", "r") as out_file:
    res = out_file.readlines()
    
    
    # Reading file until the outputs
    i = 0
    while True:
        if res[0].strip() == "CHIPS PASS" or res[0].strip() == "CHIPS FAIL":
            break
        i += 1
    res = res[i:]

    if res[0].strip() != "CHIPS PASS":
        print("CHIPS ARE NOT CORRECT. READ THE CHIPS REQUIREMENTS")
        exit(0)
    
    print("CHIPS TEST PASSED")

    # Reading results
    fail_count = 0 ; pass_count = 0
    result = open("result.txt", "w")
    for i in range(1, len(res)):
        if res[i].strip() == "FAIL":
            result.write(f"FAIL the case {i}\n")
            fail_count += 1
        else:
            result.write(f"PASS the case {i}\n")
            pass_count += 1
    result.close()
    
    print(f"PASS: {pass_count}\nFAIL: {fail_count}")
    print("Check the result.txt")
