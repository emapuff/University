class TvShows:
    def __init__(self, id, titlu, gen, nr_ep):
        self.__id = id
        self.__titlu = titlu
        self.__gen = gen
        self.__nr_ep = nr_ep

    def get_id(self):
        return self.__id

    def get_titlu(self):
        return self.__titlu

    def get_gen(self):
        return self.__gen

    def get_nr_ep(self):
        return self.__nr_ep

    def __repr__(self):
        return self.__id + ' ' + self.__titlu + ' ' + self.__gen + ' ' + str(self.__nr_ep)

    def __eq__(self, other):
        return self.__id == other.get_id()

