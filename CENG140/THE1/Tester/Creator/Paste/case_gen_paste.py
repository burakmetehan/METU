import random

colors = ["0","1","2","3","4","5","6","7"]
N = 25 # dimension
limit=N-1
shuffle_lst=[1, 2, 3, 4]

flag = 250
while(flag):
	lst=[]

	c_row_1 = random.choice(range(25))
	c_col_1 = random.choice(range(25))
	c_row_2 = random.choice(range(c_row_1, 25))
	c_col_2 = random.choice(range(c_col_1, 25))

	row_N = c_row_2 - c_row_1 + 1
	col_N = c_col_2 - c_col_1 + 1

	if c_row_1 >= row_N:
		# Condition for top
		p_row_1 = random.choice(range(c_row_1 - row_N +1))
		p_col_1 = random.choice(range(N - col_N +1))
		p_row_2 = p_row_1 + row_N -1 
		p_col_2 = p_col_1 + col_N -1
		lst.append([p_row_1, p_col_1, p_row_2, p_col_2])

	if (limit - c_col_2) >= col_N:
		# Condition for right
		p_row_1 = random.choice(range(N - row_N +1))
		p_col_1 = random.choice(range(c_col_2 +1, N - col_N +1))
		p_row_2 = p_row_1 + row_N -1
		p_col_2 = p_col_1 + col_N -1
		lst.append([p_row_1, p_col_1, p_row_2, p_col_2])

	if (limit - c_row_2) >= row_N:
		# Condition for bottom
		p_row_1 = random.choice(range(c_row_2 +1, N - row_N +1))
		p_col_1 = random.choice(range(N - col_N +1))
		p_row_2 = p_row_1 + row_N -1
		p_col_2 = p_col_1 + col_N -1
		lst.append([p_row_1, p_col_1, p_row_2, p_col_2])

	if c_col_1 >= col_N:
		# Condition for left
		p_row_1 = random.choice(range(N - row_N +1))
		p_col_1 = random.choice(range(c_col_1))
		p_row_2 = p_row_1 + row_N -1
		p_col_2 = p_col_1 + col_N -1
		lst.append([p_row_1, p_col_1, p_row_2, p_col_2])
	
	for i in range(len(lst)):
		with open(f"cases/case{250-flag}.txt", "w") as case:
			lst_image=[]
			dimension = N
			for j in range(N):
				lst_image.append(random.choices(colors, k=N))
		
			for j in range(dimension):
				case.write(" ".join(lst_image[j]))
				case.write("\n")		

			case.write("P\n")
			shuffle = random.choice(shuffle_lst)
			def my_shuffle(lst):
				s = [0, 1]
				c = random.choice(s)
				if c:
					return lst
				else:
					return lst[::-1]

			row_s = my_shuffle([c_row_1, c_row_2])
			col_s = my_shuffle([c_col_1, c_col_2])

			case.write(f"{row_s[0]} {col_s[0]} {row_s[1]} {col_s[1]}\n")

			# lst.append([p_row_1, p_col_1, p_row_2, p_col_2])

			p_row_s = my_shuffle([lst[i][0], lst[i][2]])
			p_col_s = my_shuffle([lst[i][1], lst[i][3]])
			case.write(f"{p_row_s[0]} {p_col_s[0]} {p_row_s[1]} {p_col_s[1]}\n")
		
		flag -= 1
		if flag == 0:
			flag = 0
			break
		 
		

