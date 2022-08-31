# CENG 111 THE3
# Burak Metehan Tunçel, 2468726.

# I am defining some functions that I will use them in some parts of other functions that are expected from us.
def childDeterminer(lst):
	# This function is intended for determining whether a list in nested list has tuple or not.
	# If there is not tuple, this means there is no subpart.
	if not lst:
		return True
	if type(lst[0]) == tuple:
		return False
	else:
		return childDeterminer(lst[1:])


def search(x, lst):
	# I am using this function to find appropriate parent-child couple in makeTree() function.
	for i in lst:
		for j in i:
			if type(j) == tuple and j[1] == x:
				indexI = lst.index(i)
				indexJ = i.index(j)
				return indexI, indexJ
	return False


def copy(oldList):
	# This function is intended for copying the incomingList in makeTree() function in order to
	# prevent side effects.
	newList = []
	for i in oldList:
		newList.append(i[:])
	return newList


def isNested(lst):
	# This function is intended for checking whether a list is nested or not.
	# This function is used in calculate_price() and required_parts().
	for i in lst:
		if type(i) == list:
			return True
	return False


# The following function is translating the given list (part_list) to tree-structured nested list.
def makeTree(incomingList):
	lst = copy(incomingList)  # Copying incomingList in order to prevent side effects that occur in part_list
	childList2 = []
	parentList2 = []
	# By using related function. I am create a child list and parent list for that phase.
	# I am doing it because I need to start from the last, which means deepest element.
	# By this way, I can use childList to change the tuple structure in parentList.
	# At the end of the function, there will be no element in parentList,
	# Because there will be not tuple in any element.
	for i in lst:
		if childDeterminer(i):
			childList2.append(i)
		else:
			parentList2.append(i)

	for i in childList2:
		sRes = search(i[0], parentList2)
		if sRes:
			parentList2[sRes[0]][sRes[1]] = [parentList2[sRes[0]][sRes[1]][0]] + i

	if not parentList2:
		return childList2
	else:
		childList2.clear()
		return makeTree(parentList2)


# Until this part I coded some functions to convert nested list to tree structure list.
# After here, there will be functions that are expected from me and their helpers functions.

# Function 1: (calculate_price())
def calculate_price(part_list):
	# I need to convert this part list to tree list.
	treeList = makeTree(part_list)[0]
	result = 0
	# The block of code below (if block) was added after I finalized (for the first time). Because it is indicated that
	# [["ntuevt", 115.7]] is valid case for part_list and my code has not satisfied this case, I added the block of code
	# instead of changing the whole code. The code block below just check for whether "treeList" is nested or not. As a
	# result I am able to determine whether i will calculate a nested treeList or a one element non-nested treeList.
	if not isNested(treeList):
		return treeList[-1]
	# In this situation the list just contains two elements which are name of part and its price.
	# Therefore, I had to just return the price which is the last element of the list.

	# I am taking the branches separately and calculate their value, then sum all of them.
	for i in treeList[1:]:
		result += priceCalculatorHelper(i)
	return result


def priceCalculatorHelper(treeList):
	# I will provide branch list and calculate this branch's value.
	if len(treeList) == 2:
		return 0

	if isNested(treeList):
		result = treeList[0] * priceCalculatorHelper(treeList[-1])
		return result + priceCalculatorHelper(treeList[:-1])
	else:
		return treeList[0] * treeList[2]


# Function 2: (required_parts())
def required_parts(part_list):
	treeList = makeTree(part_list)[0]
	resultList = []
	# The block of code below (if block) was added after I finalized (for the first time). Because it is indicated that
	# [["ntuevt", 115.7]] is valid case for part_list and my code has not satisfied this case, I added the block of code
	# instead of changing the whole code. The code block below just check for whether "treeList" is nested or not. As a
	# result I am able to determine whether i will handle a nested treeList or a one element non-nested treeList.
	if not isNested(treeList):
		return [(1, treeList[-2])]
	# In this situation the list just contains two elements which are name of part and its price
	# Therefore, I had to add just 1 beginning of the tuple

	# I am taking the branches separately and determine required parts, then extend the resultList which is empty.
	for i in treeList[1:]:
		resultList.extend(requiredPartsHelper(1, i, []))  
		# Providing empty list as a parameter caused a problem when I use the append method. 
		# (I am not sure but problem is probably an aliasing problem)
		# Therefore, I used the extend method.
	return resultList


def requiredPartsHelper(x, lst, newList):
	# I will provide branch list and determine required parts for that branch
	# x will probably be default 1. I will use it as default number of item.
	# lst will be the branch of tree. (First child)
	# newList will be empty list.
	if not lst:
		return

	if type(lst[0]) != list:
		if type(lst[2]) == list:
			first = lst[0]
			requiredPartsHelper(first, lst[2:], newList)
		else:
			newList.append((lst[0], lst[1]))
	elif type(lst[0]) == list:
		if isNested(lst[0]):
			requiredPartsHelper(x, lst[1:], newList)
			x *= lst[0][0]
			requiredPartsHelper(x, lst[0][2:], newList)
		else:
			result = (x*lst[0][0], lst[0][1])
			newList.append(result)
			requiredPartsHelper(x, lst[1:], newList)
	return newList


# Function 3: (stock_check())
def stock_check(part_list, stock_list):
	# In this function, I am calling the required_parts() function. Then, I am comparing the stock with that list.
	returnList = []
	reqPartsList = required_parts(part_list)
	for reqPart in reqPartsList:
		isInStock = False  # If an item is not in stock, this variable help me to know it.
		for stkPart in stock_list:
			if reqPart[1] == stkPart[1]:
				isInStock = True  # If an item is in stock, I will not go into the "not isInStock" block.
				if reqPart[0] > stkPart[0]:
					missingPart = (reqPart[1], reqPart[0]-stkPart[0])
					returnList.append(missingPart)
				break
		if not isInStock:  # If an item is not in stock, I am directly adding the item to returnList.
			returnList.append((reqPart[1], reqPart[0]))
	return returnList
