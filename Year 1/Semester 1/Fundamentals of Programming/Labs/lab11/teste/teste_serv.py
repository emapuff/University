from service.service import *
from repository.repo import *

def test_find_gen_ui():
    '''
    testeaza functia de cautare dupa gen din service
    :return:
    '''
    repo=repository('../teste.txt')
    serv=service_seriale(repo)
    repo.read_from_file()
    gen='comedy'
    new_list=serv.find_gen_ui(gen)
    assert len(new_list)==2

def test_get_preference_ui():
    '''
    testeaza functia de determinarea tipului de preferinta a serialului
    :return:
    '''
    repo = repository('../teste.txt')
    serv = service_seriale(repo)
    repo.read_from_file()
    id='COM1'
    nr_ep=50
    result=serv.get_preference_ui(id,nr_ep)
    assert result.get_preference()=='favorit'
    nr_ep = 30
    result = serv.get_preference_ui(id, nr_ep)
    assert result.get_preference() == 'if_bored'
    nr_ep=1
    result = serv.get_preference_ui(id, nr_ep)
    assert result.get_preference() == 'disliked'
