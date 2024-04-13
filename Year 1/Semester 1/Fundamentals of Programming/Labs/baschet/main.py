from repository.repo import *
from service.servoc import *
from ui.consola import *

repo=repository('read_me.txt')
serv=service(repo)
ui=main(serv)

ui.main_mini()