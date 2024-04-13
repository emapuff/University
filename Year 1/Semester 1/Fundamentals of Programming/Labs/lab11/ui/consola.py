from service import *

class consola:
    def __init__(self, serv):
        self.__serv=serv

    def print_menu(self):
        '''
        printeaza meniul
        :return:
        '''
        print('Menu:')
        print('1. cauatre gen')
        print('2. determianre preferinte')
        print('3. exit')

    def printare_ceva(self, lista):
        '''
        printeaza o lista oarecare trimisa ca parametru
        :param lista: lista care se doreste a fi printata
        :return: -
        '''
        if len(lista)==0:
            print('Nu exista')
        else:
            for i in lista:
                print(i)

    def option_1(self):
        '''
        genstioneaza cautarea dupa gen a serialelor
        :return: -
        '''
        gen=input('introduceti un gen: ')
        gen=gen.strip()
        rez=self.__serv.find_gen_ui(gen)
        self.printare_ceva(rez)

    def option_2(self):
        '''
        gestioneaza determinare a cat de preferat e un serial introdus de la tastatura
        :return:
        '''
        id=input('introduceti id-ul showului')
        id=id.strip()
        nr=input('introduceti nr de episoade vizionate')
        nr=int(nr)
        rezultat=self.__serv.get_preference_ui(id, nr)
        print (rezultat)

    def main(self):
        '''
        gestioneaza meniul
        :return:
        '''
        while True:
            self.print_menu()
            self.__serv.read_serv()
            opt=input('Introduceti optiunea:')
            opt=int(opt)
            if opt==1:
                self.option_1()
            elif opt==2:
                self.option_2()
            else:
                break