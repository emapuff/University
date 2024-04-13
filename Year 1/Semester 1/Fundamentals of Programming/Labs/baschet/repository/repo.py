from entity import *
import datetime
class repository:
    def __init__(self, file_path):
        self.__list=[]
        self.__file_path=file_path

    def get_all(self):
        return self.__list

    def get_size(self):
        return len(self.__list)

    def find_pozitie(self, pozitie):
        lista_rez=[]
        for entity in self.__list:
           if pozitie in entity.get_pozitie():
               lista_rez.append(entity)
        return lista_rez

    def find_id(self, id):
        for entity in self.__list:
            if entity.get_id()==id:
                return entity
        return None

    def adaugare(self, jucator):
        self.__list.append(jucator)

    def citire_fisier(self):
        with open(self.__file_path, 'r') as f:
            lista=f.readlines()
            for line in lista:
                date=line.split(',')
                date[0]=date[0].strip()
                date[1] = date[1].strip()
                date[2] = date[2].strip()
                if len(date)==4:
                    date[3]=int(date[3])
                    player=jucator(date[0],date[1],date[2],date[3])
                    self.__list.append(player)

