from entity import *

class MVPcandidate:
    def __init__(self, jucator, nr_meciuri):
        self.__jucator=jucator
        self.__nr_meciuri=nr_meciuri

    def get_jucator(self):
        return self.__jucator

    def get_nr_meciuri(self):
        return self.__nr_meciuri

    def get_points_average(self):
        return int(self.__jucator.get_puncte())/int(self.get_nr_meciuri())

    def __eq__(self, other):
        return self.__jucator==other.get_jucator()

    def __repr__(self):
        return self.__jucator.get_id()+" "+str(self.get_points_average())
