label = ["Name", "Price", "Type", "Category"]

def getByCat(items, category):
	return [item for item in items if item['Category'] == category]

def readInput():
	itemList = []
	count = input()
	for x in range(count):
		item = [x.strip() for x in raw_input().split(",")]
		itemPair = zip(label, item)
		itemList.append(dict(itemPair))
	return itemList

if __name__ == '__main__':
	itemList = readInput()
	category = raw_input()
	print getByCat(itemList, category)