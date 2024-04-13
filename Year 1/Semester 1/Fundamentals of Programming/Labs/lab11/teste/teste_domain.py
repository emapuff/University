from enititati import *

def test_get_id():
    obj=TvShows('C1', 'CEVA', 'DRAMA', 12)
    assert obj.get_id() == 'C1'

def test_get_titlu():
    obj=TvShows('C1', 'CEVA', 'DRAMA', 12)
    assert obj.get_titlu() == 'CEVA'

def test_get_gen():
    obj=TvShows('C1', 'CEVA', 'DRAMA', 12)
    assert obj.get_gen() == 'DRAMA'

def test_get_nr_ep():
    obj=TvShows('C1', 'CEVA', 'DRAMA', 12)
    assert obj.get_nr_ep() == 12

test_get_id()
test_get_gen()
test_get_titlu()
test_get_nr_ep()