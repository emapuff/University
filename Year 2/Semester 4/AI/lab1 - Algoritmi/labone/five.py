"""
IDEE: tratam lista ca linked list si ne folosim de
algoritmul floyd's tortoise and hare
complexitate timp O(n), complexitate spatiu theta(1)
"""


def solutie_ema(list):
    '''
    n - the number of elements in the list
    time complexity: O(n)
    space complexity: O(1)
    '''
    tortoise = list[0]
    hare = list[0]
    while True:
        tortoise = list[tortoise]
        hare = list[list[hare]]
        if tortoise == hare:
            break

    num1 = list[0]
    num2 = tortoise

    while num1 != num2:
        num1 = list[num1]
        num2 = list[num2]

    print(num1)


#chat
def gaseste_duplicat(nums):
    '''
    given n - number of elements in nums
    time complexity: theta(n)
    space complexity: O(n)
    '''
    vazute = set()
    for num in nums:
        if num in vazute:
            return num
        vazute.add(num)



#solutie_ema([1,2,3,4,2])

def test_solutie_ema():
    # Caz 1: Duplicatul este 2

    solutie_ema([3, 1, 3, 4, 2])

    solutie_ema([1, 3, 4, 2, 2]) # Output: 2

    solutie_ema([4, 3, 1, 4, 2])  # Output: 4

    solutie_ema([5, 1, 2, 3, 4, 5]) # Output: 5

    solutie_ema([6, 6, 1, 2, 3, 4, 5])  # Output: 6

test_solutie_ema()
