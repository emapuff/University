'''
Pentru un șir cu n numere întregi care conține și duplicate,
să se determine elementul majoritar (care apare de mai mult de n / 2 ori).
De ex. 2 este elementul majoritar în șirul [2,8,7,2,2,5,2,3,1,2,2].

Idee: Moore's Voting Algorithm
'''


def solutie_ema(list):
    '''
    n being the number of elements in the list
    time compelxity: O(n)
    space complexity: theta(1)
    '''
    count = 0
    candidate = list [0]
    for i in range (1, len(list)):
        if candidate != list[i]:
            count -= 1
            if count == 0:
                candidate = list[i]
        else:
            count +=1

    count = 0
    for i in range (0, len(list)):
        if candidate == list[i]: count +=1

    if count > len(list)/2: return candidate
    else: return None


def element_majoritar(lista):
    n = len(lista)

    for i in range(n):
        count = 0
        for j in range(n):
            if lista[j] == lista[i]:
                count += 1

        if count > n // 2:
            return lista[i]

    return None  # Dacă nu există element majoritar


print(solutie_ema([2,8,7,2,2,5,2,3,1,2,2]))
