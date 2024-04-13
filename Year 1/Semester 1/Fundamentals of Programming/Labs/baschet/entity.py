
class jucator:
    def __init__(self, id, nume, pozitie, puncte):
        self.__id=id
        self.__nume=nume
        self.__pozitie=pozitie
        self.__puncte=puncte

    def get_id(self):
        return self.__id

    def get_nume(self):
        return self.__nume

    def get_pozitie(self):
        return  self.__pozitie

    def get_puncte(self):
        return self.__puncte

    def __eq__(self, other):
        return self.__id==other.get_id()

    def __repr__(self):
        return self.__id+" "+self.__nume+" "+self.__pozitie+" "+str(self.__puncte)
