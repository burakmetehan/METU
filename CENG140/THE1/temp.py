#Matrix Difference Counter
while (1):
	N = int(input("Dimension: "))

	if N <= 0:
		break
	
	count = 0
	matrix_1 = []
	matrix_2 = []
	print("FirstMatrix:")
	for i in range(N):
		matrix_1.append([int(x) for x in input().split()])
		
	print("Second Matrix:")
	for i in range(N):
		matrix_2.append([int(x) for x in input().split()])

	for i in range(N):
		for j in range(N):
			if matrix_1[i][j] == matrix_2[i][j]:
				continue
			else:
				count+=1

	print("*"*15)
