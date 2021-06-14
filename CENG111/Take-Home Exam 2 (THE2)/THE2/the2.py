# CENG 111 THE2
# Burak Metehan Tunçel, 2468726.
import random
from evaluator import *    # get_data() will come from this import

"""Adjusting the variables acquired from get_data(). Then calculating probabilities"""
# Variables from get_data()
borderY = get_data()[0]
borderX = get_data()[1]
constD = get_data()[2]
constK = get_data()[3]
constL = get_data()[4]
constM = get_data()[5]
indList = get_data()[6]

# Move possibilities. Should be:
# "Forward, Forward Right, Right, Backward Right, Backward, Backward Left, Left, Forward Left"
forw = 1 / 2 * constM
forwRgh = 1 / 8 * constM
right = 1 / 2 * (1 - constM - constM ** 2)
backRgh = 2 / 5 * constM ** 2
back = 1 / 5 * constM ** 2
backLft = 2 / 5 * constM ** 2
left = 1 / 2 * (1 - constM - constM ** 2)
forwLft = 1 / 8 * constM
moveProbabilities = [forw, forwRgh, right, backRgh, back, backLft, left, forwLft]

# Lists of move ways according to possibilites
moveL0 = [0, 1, 2, 3, 4, 5, 6, 7]
moveL1 = [1, 2, 3, 4, 5, 6, 7, 0]
moveL2 = [2, 3, 4, 5, 6, 7, 0, 1]
moveL3 = [3, 4, 5, 6, 7, 0, 1, 2]
moveL4 = [4, 5, 6, 7, 0, 1, 2, 3]
moveL5 = [5, 6, 7, 0, 1, 2, 3, 4]
moveL6 = [6, 7, 0, 1, 2, 3, 4, 5]
moveL7 = [7, 0, 1, 2, 3, 4, 5, 6]
moveWays = [moveL0, moveL1, moveL2, moveL3, moveL4, moveL5, moveL6, moveL7]

# Infection Types
infecTypes = ["infected", "notinfected"]


def new_move():
	"""Processes"""
	# Calculating of movement
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
	newInfecDict = {}
	valueOne = 1
	for k in indList:
		valueK = valueOne # I am changing the valueK after next loop.
						# valueK is for showing the index number of l in main list.
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

	# Adjusting new infections status
	if len(newInfecDict) != 0:
		for k,l in newInfecDict.items():
			indList[k][3] = l

	return indList # Returning the individuals' list (universe).
