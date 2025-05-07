'''
Să se determine al k-lea cel mai mare element al unui șir de numere cu n elemente (k < n).
De ex. al 2-lea cel mai mare element din șirul [7,4,6,3,9,1] este 7.
'''

'''
Idee: folosim un max heap si apoi stergem primele k-1 elemente maxime 
time complexity: O(nlogn)
space complexity: theta(n)
'''
def heapify_up(heap, index):
    parent = (index - 1) // 2
    while index > 0 and heap[index] > heap[parent]:
        heap[index], heap[parent] = heap[parent], heap[index]
        index = parent
        parent = (index - 1) // 2


def heapify_down(heap, index):
    size = len(heap)
    while True:
        left = 2 * index + 1
        right = 2 * index + 2
        largest = index

        if left < size and heap[left] > heap[largest]:
            largest = left
        if right < size and heap[right] > heap[largest]:
            largest = right
        if largest == index:
            break

        heap[index], heap[largest] = heap[largest], heap[index]
        index = largest


def insert(heap, value):
    heap.append(value)
    heapify_up(heap, len(heap) - 1)

def delete(heap, index):
    """ Șterge elementul de la indexul dat din max-heap """
    if index >= len(heap):
        return

    heap[index] = heap[-1]
    heap.pop()

    if index < len(heap):
        parent = (index - 1) // 2
        if index > 0 and heap[index] > heap[parent]:
            heapify_up(heap, index)
        else:
            heapify_down(heap, index)

def extract_max(heap):

    if len(heap) == 0:
        return None

    max_value = heap[0]
    heap[0] = heap[-1]
    heap.pop()

    if len(heap) > 0:
        heapify_down(heap, 0)

    return max_value

def max_k(list,k):
    heap =[]
    for i in list:
        insert(heap,i)

    for i in range(k-1):
        delete(heap,0)

    return heap[0]

print(max_k([7,4,6,3,9,1],2))

'''
time complexity: O(n + nlogn)
'''
def kth_largest_element(arr, k):
    arr.sort(reverse=True)  # Sortăm în ordine descrescătoare
    return arr[k - 1]