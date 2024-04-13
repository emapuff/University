from repository.repo import *
from entity import *

def test_adaugare():
    repo=repository('../teste.txt')
    repo.adaugare(jucator('G01','Dwain','fundas',120))
    n=repo.get_size()
    assert n==1
    repo.adaugare(jucator('G02', 'Denis', 'atacant', 40))
    n=repo.get_size()
    assert n==2

def test_find_pozitie():
    repo = repository('../teste.txt')
    repo.adaugare(jucator('G01', 'Dwain', 'fundas', 120))
    repo.adaugare(jucator('G02', 'Denis', 'atacant', 40))
    obj=repo.find_pozitie('fundas')
    assert len(obj)==1
    obj=repo.find_pozitie('denis')
    assert len(obj)==0


def test_citire_fisier():
    repo = repository('../teste.txt')
    repo.citire_fisier()
    n=repo.get_size()
    assert n==2

def test_find_id():
    repo = repository('../teste.txt')
    repo.adaugare(jucator('G01', 'Dwain', 'fundas', 120))
    repo.adaugare(jucator('G02', 'Denis', 'atacant', 40))
    obj=repo.find_id('G01')
    assert obj==jucator('G01', 'Dwain', 'fundas', 120)