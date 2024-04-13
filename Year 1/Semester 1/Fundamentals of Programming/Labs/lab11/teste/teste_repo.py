from repository.repo import *

def test_adaugare():
    '''
    testeaza functia de adaugare din repo
    :return:
    '''
    repo=repository('../teste.txt')
    repo.adaugare(TvShows('C1','CEVA','DRAMA',12))
    repo.adaugare(TvShows('C1','CEVA','DRAMA',12))
    n=repo.get_size()
    assert n==2

def test_find_id():
    '''
    testeaza functia de cautare dupa id
    :return:
    '''
    repo = repository('../teste.txt')
    repo.adaugare(TvShows('C1', 'CEVA', 'DRAMA', 12))
    repo.adaugare(TvShows('C2', 'aktEVA', 'comedy', 12))
    obj=repo.find_id('C1')
    assert obj==TvShows('C1', 'CEVA', 'DRAMA', 12)

def test_find_gen():
    '''
    testeaza functia de cautare dupa gen
    :return:
    '''
    new_list=[]
    repo = repository('../teste.txt')
    repo.adaugare(TvShows('C1', 'CEVA', 'DRAMA', 12))
    repo.adaugare(TvShows('C2', 'aktEVA', 'comedy', 12))
    new_list=repo.find_gen('comedy')
    assert len(new_list)==1

def test_read_from_file():
    '''
    testeaza functia de citire din fisier
    :return:
    '''
    repo = repository('../teste.txt')
    repo.read_from_file()
    n=repo.get_size()
    assert n==4

test_adaugare()
test_find_id()
test_read_from_file()
test_find_gen()
