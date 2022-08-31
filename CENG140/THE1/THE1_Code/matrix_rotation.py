import copy

def rotate_R_90(matrix, newMatrix):
	for i in range(N):
		for j in range(N):
			newMatrix[i][j] = matrix[N-j-1][i]

def rotate_L_90(matrix, newMatrix):
	for i in range(N):
		for j in range(N):
			newMatrix[i][j] = matrix[j][N-i-1]

def rotate_180(matrix, newMatrix):
	for i in range(N):
		for j in range(N):
			newMatrix[i][j] = matrix[N-1-i][N-1-j]

def matrix_print(newMatrix):
	print("New Matrix:")
	for i in range(N):
		print(*newMatrix[i])


while (1):
	turn_letter = input("Turn Letter: ").upper()
	turn_degree = int(input("Turn Degree: "))
	N = int(input("Dimension: "))

	if turn_letter == "Q":
		break
	if turn_degree == -1:
		break
	
	matrix = []
	print("Matrix:")
	for i in range(N):
		matrix.append([int(x) for x in input().split()])

	newMatrix = copy.deepcopy(matrix)

	if turn_degree == 0:
		matrix_print(newMatrix)
	elif turn_degree == 180:
		rotate_180(matrix, newMatrix)
		matrix_print(newMatrix)
	elif (turn_letter == "R" and turn_degree == 90) or (turn_letter == "L" and turn_degree == 270):
		rotate_R_90(matrix, newMatrix)
		matrix_print(newMatrix)
	else:
		rotate_L_90(matrix, newMatrix)
		matrix_print(newMatrix)

	print("*"*15)
