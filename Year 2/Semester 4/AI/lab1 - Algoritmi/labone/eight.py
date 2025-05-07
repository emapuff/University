'''
Să se genereze toate numerele (în reprezentare binară) cuprinse între 1 și n.
 De ex. dacă n = 4, numerele sunt: 1, 10, 11, 100.
'''
from queue import Queue

def solutie_ema(n):
    '''
    time complexity: theta(n)
    space complexity: theta(n)
    '''
    queue = Queue()
    queue.put("1")

    while n>0:
        n-=1
        head = queue.get()
        print(head)

        queue.put(head+"0")
        queue.put(head+"1")

solutie_ema(4)


def generatePrintBinary(n):
    '''
    time complexity: theta(n*logn)
    '''
    for i in range(1, n + 1):
        str = ""
        temp = i
        while temp:
            if temp & 1:
                str = "1" + str
            else:
                str = "0" + str
            temp >>= 1
        print(str)