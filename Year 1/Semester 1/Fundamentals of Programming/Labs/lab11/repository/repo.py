from enititati import *

class repository:
    def __init__(self, file):
        self.__list=[]
        self.__file=file

    def get_all(self):
        '''

        :return: toata lista cu entitati
        '''
        return self.__list

    def get_size(self):
        '''
        :return: lungimea listei
        '''
        return len(self.__list)

    def find_id(self, id):
        '''
        gaseste un serial in functie de id
        :param id: id-ul cautat
        :ptype: int
        :return: serial ul gasit
        :rtype: TvShow
        '''
        for i in self.__list:
            if i.get_id()==id:
                return i
        return None

    def find_gen(self, gen):
        '''
        gaseste toate serialele care au in gen un string introdus
        :param: gen-ul cautat
        :ptype: str
        :return: lista cu toate serialele gasite
        :rtype: list
        '''
        new_list=[]
        for i in self.__list:
            if gen in i.get_gen():
                new_list.append(i)
        return new_list

    def adaugare(self, obiect):
        '''
        adauga un serial nou in lista
        :param obiect: serialul
        :ptype: TvShow - obiect
        :return: -
        '''
        self.__list.append(obiect)

    def read_from_file(self):
        '''
        citeste din fisier datele
        :return: -
        '''
        with open(self.__file, 'r') as f:
            lista=f.readlines()
            for line in lista:
                data=line.split(',')
                if len(data)==4:
                    data[0]=data[0].strip()
                    data[1] = data[1].strip()
                    data[2] = data[2].strip()
                    data[3]=int(data[3])
                    show=TvShows(data[0],data[1],data[2],data[3])
                    self.adaugare(show)

