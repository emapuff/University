from enititati import *

class ShowEvaluation:
    def __init__(self, TvShow, nr_episoade):
        self.__TvShow=TvShow
        self.__nr_episoade=nr_episoade

    def get_TvShow(self):
        return self.__TvShow

    def get_nr_episoade(self):
        return self.__nr_episoade

    def get_preference(self):
        n=self.get_nr_episoade()
        if n>0.6*self.__TvShow.get_nr_ep():
            return "favorit"
        elif n>0.3*self.__TvShow.get_nr_ep():
            return "if_bored"
        else:
            return "disliked"

    def __str__(self):
        return self.__TvShow.get_titlu()+' '+self.__TvShow.get_gen()+' '+self.get_preference()

    def __eq__(self, other):
        return self.__TvShow==other.get_TvShow()