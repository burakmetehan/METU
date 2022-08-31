def create_truth_table(n: int) -> list:
    if n <= 1:
        return [[0], [1]]
    else:
        lst = create_truth_table(n-1)
        new_list = []
        for i in range(2):
            for x in lst:
                temp = [i]
                temp.extend(x)
                new_list.append(temp)
        return new_list


def execute(row: list) -> str: # One row of the truth table
    row = ''.join([str(x) for x in row]) # converting row to str
    op_code = row[0:3]
    var_A = row[3:5]
    var_B = row[5:7]
    res_out = ['0']*8

    if op_code == '000': # B + A
        res = eval(f"0b{var_B} + 0b{var_A}") # 0b{var_B} evals the var_B as binary
    elif op_code == '001': # B - A
        res = eval(f"0b{var_B} - 0b{var_A}")
        if res < 0:
            res_out[-1] = '1' # sign bit change
            res = abs(res) # value absolute val
    elif op_code == '010': # B << A
        res = eval(f"0b{var_B} << 0b{var_A}")
        if res > 6: # res cannot be shown, it shouldn't be include since it cannot be tested
            return ""
    elif op_code == "011": # B >= A
        res = 1 if eval(f"0b{var_B} >= 0b{var_A}") else 0
    elif op_code == "100": # B ^ A (bitwise xor)
        res = eval(f"0b{var_B} ^ 0b{var_A}")
    elif op_code == "101": # B & A (bitwise and)
        res = eval(f"0b{var_B} & 0b{var_A}")
    elif op_code == "110": # neg(B | A): negation of bitwise or. 
        res = eval(f"(0b{var_B} | 0b{var_A})^3") #(0bxx)^3 is negation: (0bxx) ^ (0b11)
    elif op_code == "111": # No such op_code
        return ""
    else:
        print("ERROR: EXIT")
        exit(0)

    res_out[res] = '1' # this will be shown: Lx
    res_out.reverse() # output is reverse
    
    res_str = ",".join(row) + ";" + ",".join(res_out)

    return res_str


table = create_truth_table(7)

# Test cases are generated
test_cases = []
for row in table:
    main_str = execute(row)
    if main_str == "":
        continue

    test_cases.append(main_str)


with open("grader-hw2.properties", "w") as io:
    io.write("""allowed_chips= \\
    Base:Pin, \\
    Base:Text, \\
    CENG232 Gates:NOT Gate, \\
    CENG232 Gates:AND Gate, \\
    CENG232 Gates:OR Gate, \\
    CENG232 Gates:Controlled Inverter, \\
    CENG232 Gates:NOR Gate, \\
    CENG232 Gates:NAND Gate, \\
    CENG232 Gates:XOR Gate, \\
    CENG232 ICs:4-to-1 MUX (x2) (74153), \\
    CENG232 ICs:3-to-8 decoder (74138), \\
    CENG232 Gates:Constant\n\n""")

    io.write("inputs=O2,O1,O0,A1,A0,B1,B0\n") #Input Names
    io.write("outputs=S,L6,L5,L4,L3,L2,L1,L0\n\n") #Output Names
    
    io.write(f"number_of_runs={len(test_cases)}\n")

    for run, item in enumerate(test_cases):
        io.write(
                f"run.{run+1}.length = 1".strip() + "\n" + \
                f"run.{run+1}.state.1 = {item}".strip() + "\n")
