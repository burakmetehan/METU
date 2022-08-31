import random


colors = [0,1,2,3,4,5,6,7]


flag=5
while(flag):
	lst=[]
	dimension = 15
	for i in range(dimension):
		lst2=[]
		for j in range(dimension):
			lst2.append(str(random.choice(colors)))
		lst.append(lst2)
	
	for i in range(dimension):
		print(" ".join(lst[i]))
	
	print()
		
	flag-=1
