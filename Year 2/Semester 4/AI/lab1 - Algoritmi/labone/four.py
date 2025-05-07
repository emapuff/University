''''
IDEE: dictionar de cuvinte :)
cheie - cuvant
valoare - nr de aparitii
'''


def solutie_ema(text):
    # vector de cuvinte
    '''
    given n - the number of words in the text
    time complexity theta(n) + O(n)
    space complexity:
    '''
    words = text.split()
    dict = {}
    for word in words:
        dict[word] = dict.get(word, 0) + 1

    for key, value in dict.items():
        if value == 1:
            print(key)

def solutie_chat(text):
    '''
    given n - the number of words in the text
    time complexity: theta(n) + theta(n)
    '''
    # Împărțim textul în cuvinte
    cuvinte = text.split()
    # Numărăm aparițiile fiecărui cuvânt
    frecventa = {}
    for cuvant in cuvinte:
        if cuvant in frecventa:
            frecventa[cuvant] += 1
        else:
            frecventa[cuvant] = 1
    # Selectăm cuvintele care apar exact o dată
    cuvinte_unice = [cuvant for cuvant, count in frecventa.items() if count == 1]
    return cuvinte_unice


solutie_ema("ema ema are mere mere si merge pe pe munte")
solutie_chat("ema ema are mere mere si merge pe pe munte")
