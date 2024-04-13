from service.servoc import *
from repository.repo import *
from dto import *

def test_find_pozitie_ui():
    repo=repository('../teste.txt')
    serv = service(repo)
    repo.citire_fisier()
    obj=serv.find_pozitie_ui('fundas')
    assert len(obj)==1

def test_evalu_evolution():
    repo = repository('../teste.txt')
    serv = service(repo)
    repo.citire_fisier()
    nr_meciuri=10
    id='G001'
    obj=serv.evalu_evolution(id, nr_meciuri)
    assert obj.get_points_average()==12
