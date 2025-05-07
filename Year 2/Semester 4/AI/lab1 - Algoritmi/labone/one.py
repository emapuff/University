
# IDEE: parcurg sirul la citire si retin maximul
# complexitate timp : theta(n)
# comlexitate mem: theta(1)
# varianta mea
def varianta_Ema():
    string = input('Enter a string: ')
    string = string.split(' ')
    max_string = string[0]

    for i in range (0, len(string)):
        if string[i] > max_string:
            max_string = string[i]

    print("Final string is ", max_string)

#varianta bot

def varitanta_Chat():
    string = input('Enter a string: ')
    cuvinte = string.split()
    print (max(cuvinte))

varianta_Ema()
varitanta_Chat()