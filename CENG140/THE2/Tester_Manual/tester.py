

manual = open("./tester_output_manual", "r")
creator = open("./tester_creator_output", "r")

man = manual.read().splitlines()
crtr = creator.read().splitlines()

""" First Check """
for i in range(len(man)):
	if man[i] == crtr[i]:
		print("Line {} is True".format(i+1))
	else:
		print("Line {} is False".format(i+1))

""" Second Check: Detail Check """
for i in range(len(man)):
	man_detail = man[i].split()
	crtr_detail = crtr[i].split()
	correct = 1
	for j in range(len(man_detail)):
		if man_detail[j] == crtr_detail[j]:
			continue
		else:
			correct = 0
			print("Line {}/{} is False".format(i+1, j+1))
	
	if correct:
		print("Line {} is True".format(i+1))


manual.close()
creator.close()