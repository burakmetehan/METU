from os import close


manual = open("./result", "r")
function = open("./temp", "r")

man = manual.read().splitlines()
func = function.read().splitlines()

""" First Check """
print("First Check")
for i in range(len(man)):
	if man[i] == func[i]:
		print("Line {} is True".format(i+1))
	else:
		print("Line {} is False".format(i+1))

print("Second Check")
""" Second Check: Detail Check """
for i in range(len(man)):
	man_detail = man[i].split()
	func_detail = func[i].split()
	correct = 1
	for j in range(len(man_detail)):
		if man_detail[j] == func_detail[j]:
			continue
		else:
			correct = 0
			print("Line {}/{} is False".format(i+1, j+1))
	
	if correct:
		print("Line {} is True".format(i+1))


manual.close()
function.close()