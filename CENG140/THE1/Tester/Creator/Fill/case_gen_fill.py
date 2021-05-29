import random
import os

colors = ["0","1","2","3","4","5","6","7"]
N = 25 # dimension


for file_no in range(250):
	lst_fill=[]		
	with open(f"cases/case{file_no}.txt", "w") as case:
		for _ in range(N):
			lst_fill.append(random.choices(colors, k=N))
		
		for i in range(N):
			case.write(" ".join(lst_fill[i]))
			case.write("\n")
			
		color_coor = [str(random.choice(range(-100,100))), str(random.choice(range(-100,100)))]
		pixel_coor = [str(random.choice(range(0,25))), str(random.choice(range(0,25)))]
		case.write("F\n")			
		case.write(" ".join(color_coor))
		case.write("\n")
		case.write(" ".join(pixel_coor))
