from repository.repo import *
from dto import *
class service():
    def __init__(self, repo):
        self.__repo=repo

    def get_all_serv(self):
        return self.__repo.get_all()

    def get_size_serv(self):
        return self.__repo.get_size()

    def find_pozitie_ui(self, pozitie):
        new_list=self.__repo.find_pozitie(pozitie)
        return new_list

    def evalu_evolution(self, id, nr_meciuri):
        player=self.__repo.find_id(id)
        new_something=MVPcandidate(player,nr_meciuri)
        return new_something

    def citire(self):
        self.__repo.citire_fisier()