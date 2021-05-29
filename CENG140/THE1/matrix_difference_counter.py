#Matrix Difference Counter
while (1):
	N_row = int(input("Row Dimension: "))
	N_col = int(input("Col Dimension: "))

	if N_row <= 0 or N_col <= 0:
		break
	
	count = 0
	matrix_1 = []
	matrix_2 = []
	print("FirstMatrix:")
	for i in range(N_row):
		matrix_1.append([int(x) for x in input().split()])
		
	print("Second Matrix:")
	for i in range(N_row):
		matrix_2.append([int(x) for x in input().split()])

	for i in range(N_row):
		for j in range(N_col):
			if matrix_1[i][j] == matrix_2[i][j]:
				continue
			else:
				count+=1
	
	print("Difference: ", count)
	print("*"*15)
