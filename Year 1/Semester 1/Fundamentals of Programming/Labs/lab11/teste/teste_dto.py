
from dto import *

def test_TvShow():
    obj=TvShows('C1', 'CEVA', 'DRAMA', 12)
    nr_ep = 50
    result = ShowEvaluation(obj, nr_ep)
    assert result.get_TvShow()==TvShows('C1', 'CEVA', 'DRAMA', 12)

def test_get_nr_episoade():
    obj=TvShows('C1', 'CEVA', 'DRAMA', 12)
    nr_ep = 50
    result = ShowEvaluation(obj, nr_ep)
    assert result.get_nr_episoade()==50

def test_get_preference():
    obj=TvShows('C1', 'CEVA', 'DRAMA', 12)
    nr_ep = 50
    result = ShowEvaluation(obj, nr_ep)
    string=result.get_preference()
    assert string=='favorit'