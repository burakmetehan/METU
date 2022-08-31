from the2 import *
import pdb

def testCase1():
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

	for i in range(1, 16):
		a = eval("return{}".format(i))
		returnList.extend([a])

	for i in range(15):
		if new_move() == returnList[i]:
			print(True)
		else:
			print(False)


def testCase2():
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


def testCase3():
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

testCase1()
