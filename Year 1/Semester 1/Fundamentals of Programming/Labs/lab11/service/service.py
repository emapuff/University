from repository import *
from dto import *

class service_seriale():
    def __init__(self, repo):
        self.__repo=repo

    def get_all_s(self):
        return self.__repo.get_all()

    def get_size_s(self):
        return self.__repo.get_size()

    def find_gen_ui(self, gen):
        '''
        cauta un serial dupa gen - partea de ui
        :param gen: string-ul cautat in gen
        :ptype: str
        :return: lista cu toate serialele care se incadrau in gen
        :rtype: list
        '''
        new_list=[]
        new_list=self.__repo.find_gen(gen)
        return new_list

    def get_preference_ui(self, id, nr_ep):
        '''
        determina cat de preferat este un serial de utilizator
        :param id: id-ul serialului pt care se face statistica
        :param nr_ep: nr de episoade pe care le a vizionar utilizatorului
        :ptype: str
        :ptype:int
        :return: titlul serialului, genul si daca e favorit, if_bored sau disliked
        :rtype: ShowEvaluation obiect
        '''
        nr_ep=int(nr_ep)
        obj=self.__repo.find_id(id)
        new_something=ShowEvaluation(obj,nr_ep)
        return new_something

    def read_serv(self):
        '''
        face legatura intre consola si citirea din repo
        :return:
        '''
        self.__repo.read_from_file()
