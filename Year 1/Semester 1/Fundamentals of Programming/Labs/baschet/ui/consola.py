from service.servoc import *

class main:
    def __init__(self, servo):
        self.__servo=servo

    def print_menu(self):
        print('Alegeti optiunea: ')
        print('1.cautare')
        print('2.evaluare')
        print('3. exit')

    def print_ceva(self, lista):
        if len(lista)==0:
            print('Nu exista elemente')
        else:
            for entity in lista:
                print(entity)

    def op1(self):
        ceva=input('introduceti pozitia')
        lista=self.__servo.find_pozitie_ui(ceva)
        self.print_ceva(lista)

    def op2(self):
        id=input('introduceti id-ul jucatorului')
        nr=input('introduceti nr de meciuri')
        rez=self.__servo.evalu_evolution(id, nr)
        print (rez)

    def main_mini(self):
        while True:
            self.print_menu()
            self.__servo.citire()
            opt=input('Introduceti optiunea:')
            opt=int(opt)
            if opt==1:
                self.op1()
            elif opt==2:
                self.op2()
            else:
                break


