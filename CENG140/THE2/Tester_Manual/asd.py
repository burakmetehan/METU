lst = []

for i in range(6):
	lst.append([])
	for j in range(5):
		lst[i].append([])
		gelen = input()
		gelen = gelen.split()
		for k in gelen:
			lst[i][j].append(float(k))

sum = 0
general_sum = 0
lst2 = []
laps = []
for i in range(6):
	laps.append([])
	general_sum = 0
	for j in range(5):
		sum = 0
		for k in range(3):
			sum += lst[i][j][k]
		general_sum += sum
		laps[i].append(sum)
		print("{:.2f} ".format(sum), end="")
	lst2.append(general_sum)
	print()

for i in range(6):
	for j in range(i+1,6):
		total = 0
		for k in range(5):
			total += laps[i][k]-laps[j][k]
			print("{:.2f} ".format(total), end="")
		print()