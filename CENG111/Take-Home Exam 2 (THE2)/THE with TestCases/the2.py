import math
from evaluator import *    # get_data() will come from this import
# Variables from get_data()
borderY = get_data()[0]
borderX = get_data()[1]
constD = get_data()[2]
constK = get_data()[3]
constL = get_data()[4]
constM = get_data()[5]
indList = get_data()[6]

# Move possibilities
# Should be 
#"Forward, Forward Right, Right, Backward Right, Backward, Backward Left, Left, Forward Left"
forw = 1/2 * constM
forwRgh = 1/8 * constM
right = 1/2 * (1-constM-constM**2)
backRgh = 2/5 * constM**2
back = 1/5 * constM**2
backLft = 2/5 * constM**2
left = 1/2 * (1-constM-constM**2)
forwLft = 1/8 * constM
moveProbabilities = [forw, forwRgh, right, backRgh, back, backLft, left, forwLft]

# Lists of move ways according to possibilites
moveL0 = [0,1,2,3,4,5,6,7]
moveL1 = [1,2,3,4,5,6,7,0]
moveL2 = [2,3,4,5,6,7,0,1]
moveL3 = [3,4,5,6,7,0,1,2]
moveL4 = [4,5,6,7,0,1,2,3]
moveL5 = [5,6,7,0,1,2,3,4]
moveL6 = [6,7,0,1,2,3,4,5]
moveL7 = [7,0,1,2,3,4,5,6]
moveWays = [moveL0, moveL1, moveL2, moveL3, moveL4, moveL5, moveL6, moveL7]

# Infection Types
infecTypes = ["infected","notinfected"]

newInfecDict = {}

def new_move():
	for i in indList:
		# Choosing moveL list to choose the new move
		moveL = moveWays[i[1]]
		move = random.choices(moveL, moveProbabilities)[0]

		# Changing values of X and Y according to move.
		if move == 0:
			newPos = i[0][0], i[0][1]+1
		elif move == 1:
			newPos = i[0][0]-1, i[0][1]+1
		elif move == 2:
			newPos = i[0][0]-1, i[0][1]
		elif move == 3:
			newPos = i[0][0]-1, i[0][1]-1
		elif move == 4:
			newPos = i[0][0], i[0][1]-1
		elif move == 5:
			newPos = i[0][0]+1, i[0][1]-1
		elif move == 6:
			newPos = i[0][0]+1, i[0][1]
		elif move == 7:
			newPos = i[0][0]+1, i[0][1]+1

		# Controlling for preoccupied places.
		for j in indList:
			if newPos == j[0]:
				newPos = i[0]
				move = i[1]

		# Controlling for going outside.
		if (newPos[0] == borderX) or (newPos[0] < 0) or (newPos[1] == borderY) or (newPos[1] < 0):
			newPos = i[0]
			move = i[1]

		# Adjusting X and Y values
		i[0] = newPos
		i[1] = move

	# Calculating new infection status
	infecHelper() # Returning the new infection status in a dictionary

	# Adjusting new infections status
	if len(newInfecDict) != 0:
		for k,l in newInfecDict.items():
			indList[k][3] = l

	return indList # Returning the individuals' list


def infecHelper():
	valueOne = 1
	for k in indList:
		valueK = valueOne # I am changing the valueK after next loop.
						# valueK is for showing the index number of J in main list.

		for l in indList[indList.index(k)+1:]:
			dist = ((k[0][0]-l[0][0])**2 + (k[0][1]-l[0][1])**2)**0.5
			if (k[3],l[3]) == ("notinfected","infected") or (k[3],l[3]) == ("infected","notinfected"):
				if dist <= constD:
					infecRate = min(1, constK/(dist**2))
					if (k[2],l[2]) == ("masked","notmasked") or (k[2],l[2]) == ("notmasked","masked"):
						infecRate /= constL
					elif (k[2],l[2]) == ("masked","masked"):
						infecRate /= (constL**2)
					
					infecProb = [infecRate,1-infecRate]
					newInfecStat = random.choices(infecTypes,infecProb)[0]
					if k[3] == "notinfected":
						if newInfecStat == "infected":
							newInfecDict.update({indList.index(k): newInfecStat})
					elif l[3] == "notinfected":
						if newInfecStat == "infected":
							newInfecDict.update({valueK: newInfecStat})			
			valueK += 1
		valueOne += 1
	return newInfecDict




"""
# Test Case 1
# get_data(): [50, 100, 5, 80, 30, 0.55, [[(22, 14), 0, 'notmasked', 'notinfected'], [(19, 15), 7, 'notmasked', 'notinfected'], [(17, 16), 7, 'notmasked', 'notinfected'], [(26, 20), 3, 'notmasked', 'infected'], [(22, 21), 5, 'masked', 'infected'], [(25, 21), 3, 'notmasked', 'infected']]]
return1 = [[(23, 13), 5, 'notmasked', 'notinfected'], [(20, 16), 7, 'notmasked', 'notinfected'], [(18, 16), 6, 'notmasked', 'notinfected'], [(27, 20), 6, 'notmasked', 'infected'], [(23, 21), 6, 'masked', 'infected'], [(26, 21), 6, 'notmasked', 'infected']]
return2 = [[(24, 12), 5, 'notmasked', 'notinfected'], [(21, 17), 7, 'notmasked', 'notinfected'], [(18, 17), 0, 'notmasked', 'notinfected'], [(28, 20), 6, 'notmasked', 'infected'], [(22, 21), 2, 'masked', 'infected'], [(26, 22), 0, 'notmasked', 'infected']]
return3 = [[(25, 11), 5, 'notmasked', 'notinfected'], [(22, 18), 7, 'notmasked', 'notinfected'], [(19, 16), 5, 'notmasked', 'notinfected'], [(28, 19), 4, 'notmasked', 'infected'], [(21, 20), 3, 'masked', 'infected'], [(27, 21), 5, 'notmasked', 'infected']]
return4 = [[(26, 10), 5, 'notmasked', 'notinfected'], [(21, 18), 2, 'notmasked', 'notinfected'], [(20, 17), 7, 'notmasked', 'notinfected'], [(27, 19), 2, 'notmasked', 'infected'], [(21, 21), 0, 'masked', 'infected'], [(28, 20), 5, 'notmasked', 'infected']]
return5 = [[(27, 9), 5, 'notmasked', 'notinfected'], [(20, 18), 2, 'notmasked', 'notinfected'], [(21, 17), 6, 'notmasked', 'notinfected'], [(26, 20), 1, 'notmasked', 'infected'], [(21, 22), 0, 'masked', 'infected'], [(29, 19), 5, 'notmasked', 'infected']]
return6 = [[(26, 8), 3, 'notmasked', 'notinfected'], [(21, 18), 6, 'notmasked', 'infected'], [(20, 16), 3, 'notmasked', 'notinfected'], [(25, 19), 3, 'notmasked', 'infected'], [(20, 21), 3, 'masked', 'infected'], [(28, 18), 3, 'notmasked', 'infected']]
return7 = [[(25, 7), 3, 'notmasked', 'notinfected'], [(20, 17), 3, 'notmasked', 'infected'], [(19, 15), 3, 'notmasked', 'infected'], [(24, 19), 2, 'notmasked', 'infected'], [(20, 22), 0, 'masked', 'infected'], [(29, 17), 5, 'notmasked', 'infected']]
return8 = [[(24, 7), 2, 'notmasked', 'notinfected'], [(20, 16), 4, 'notmasked', 'infected'], [(18, 14), 3, 'notmasked', 'infected'], [(25, 19), 6, 'notmasked', 'infected'], [(21, 22), 6, 'masked', 'infected'], [(30, 16), 5, 'notmasked', 'infected']]
return9 = [[(25, 8), 7, 'notmasked', 'notinfected'], [(21, 15), 5, 'notmasked', 'infected'], [(19, 15), 7, 'notmasked', 'infected'], [(25, 20), 0, 'notmasked', 'infected'], [(22, 21), 5, 'masked', 'infected'], [(30, 17), 0, 'notmasked', 'infected']]
return10 = [[(26, 8), 6, 'notmasked', 'notinfected'], [(21, 14), 4, 'notmasked', 'infected'], [(20, 16), 7, 'notmasked', 'infected'], [(26, 21), 7, 'notmasked', 'infected'], [(21, 21), 2, 'masked', 'infected'], [(30, 18), 0, 'notmasked', 'infected']]
return11 = [[(25, 9), 1, 'notmasked', 'notinfected'], [(21, 13), 4, 'notmasked', 'infected'], [(21, 17), 7, 'notmasked', 'infected'], [(27, 22), 7, 'notmasked', 'infected'], [(20, 20), 3, 'masked', 'infected'], [(31, 18), 6, 'notmasked', 'infected']]
return12 = [[(24, 10), 1, 'notmasked', 'infected'], [(22, 14), 7, 'notmasked', 'infected'], [(22, 16), 5, 'notmasked', 'infected'], [(27, 23), 0, 'notmasked', 'infected'], [(20, 21), 0, 'masked', 'infected'], [(30, 19), 1, 'notmasked', 'infected']]
return13 = [[(23, 9), 3, 'notmasked', 'infected'], [(23, 14), 6, 'notmasked', 'infected'], [(23, 17), 7, 'notmasked', 'infected'], [(27, 24), 0, 'notmasked', 'infected'], [(20, 22), 0, 'masked', 'infected'], [(29, 20), 1, 'notmasked', 'infected']]
return14 = [[(22, 8), 3, 'notmasked', 'infected'], [(24, 13), 5, 'notmasked', 'infected'], [(24, 18), 7, 'notmasked', 'infected'], [(28, 24), 6, 'notmasked', 'infected'], [(21, 21), 5, 'masked', 'infected'], [(28, 19), 3, 'notmasked', 'infected']]
return15 = [[(21, 7), 3, 'notmasked', 'infected'], [(25, 12), 5, 'notmasked', 'infected'], [(25, 18), 6, 'notmasked', 'infected'], [(28, 25), 0, 'notmasked', 'infected'], [(20, 21), 2, 'masked', 'infected'], [(27, 18), 3, 'notmasked', 'infected']]
returnList = []

for i in range(1,16):
	a = "return{}".format(i)
	a = eval(a)
	returnList.extend([a])

for i in range(15):
	if new_move() == returnList[i]:
		print(True)
	else:
		print(False)
"""

"""
# Test Case 2
# get_data(): [50, 100, 5,  80,  30,  0.55,  [[(34, 21), 4, 'notmasked', 'notinfected'] , [(27, 28), 2, 'notmasked', 'notinfected'] , [(40, 28), 6, 'notmasked', 'infected'] , [(34, 33), 2, 'masked', 'notinfected']]]

return1 = [[(33, 22), 1, 'notmasked', 'notinfected'], [(26, 28), 2, 'notmasked', 'notinfected'], [(41, 27), 5, 'notmasked', 'infected'], [(35, 32), 5, 'masked', 'notinfected']]
return2 = [[(32, 22), 2, 'notmasked', 'notinfected'], [(27, 27), 5, 'notmasked', 'notinfected'], [(42, 26), 5, 'notmasked', 'infected'], [(36, 31), 5, 'masked', 'notinfected']]
return3 = [[(32, 21), 4, 'notmasked', 'notinfected'], [(28, 26), 5, 'notmasked', 'notinfected'], [(41, 27), 1, 'notmasked', 'infected'], [(37, 32), 7, 'masked', 'notinfected']]
return4 = [[(33, 20), 5, 'notmasked', 'notinfected'], [(29, 25), 5, 'notmasked', 'notinfected'], [(40, 28), 1, 'notmasked', 'infected'], [(37, 31), 4, 'masked', 'notinfected']]
return5 = [[(34, 20), 6, 'notmasked', 'notinfected'], [(28, 25), 2, 'notmasked', 'notinfected'], [(39, 29), 1, 'notmasked', 'infected'], [(36, 32), 1, 'masked', 'notinfected']]
returnList = []

for i in range(1,6):
	a = "return{}".format(i)
	a = eval(a)
	returnList.extend([a])

for i in range(5):
	if new_move() == returnList[i]:
		print(True)
	else:
		print(False)
"""

"""
# Test Case 3
# get_data(): [100, 100, 5,  70,  30,  0.50,  [[(12, 18), 5, 'masked', 'infected'] , [(25, 30), 3, 'notmasked', 'infected'] , [(50, 40), 1, 'notmasked', 'notinfected'] , [(66, 10), 7, 'masked', 'notinfected']]]

return1 = [[(11, 17), 3, 'masked', 'infected'], [(24, 29), 3, 'notmasked', 'infected'], [(50, 41), 0, 'notmasked', 'notinfected'], [(65, 11), 1, 'masked', 'notinfected']]
return2 = [[(12, 16), 5, 'masked', 'infected'], [(25, 30), 7, 'notmasked', 'infected'], [(50, 42), 0, 'notmasked', 'notinfected'], [(64, 12), 1, 'masked', 'notinfected']]
return3 = [[(13, 17), 7, 'masked', 'infected'], [(26, 31), 7, 'notmasked', 'infected'], [(50, 41), 4, 'notmasked', 'notinfected'], [(63, 11), 3, 'masked', 'notinfected']]
return4 = [[(12, 18), 1, 'masked', 'infected'], [(27, 32), 7, 'notmasked', 'infected'], [(50, 40), 4, 'notmasked', 'notinfected'], [(63, 12), 0, 'masked', 'notinfected']]
return5 = [[(13, 19), 7, 'masked', 'infected'], [(27, 33), 0, 'notmasked', 'infected'], [(49, 40), 2, 'notmasked', 'notinfected'], [(62, 13), 1, 'masked', 'notinfected']]
returnList = []

for i in range(1,6):
	a = "return{}".format(i)
	a = eval(a)
	returnList.extend([a])

for i in range(5):
	if new_move() == returnList[i]:
		print(True)
	else:
		print(False)
"""