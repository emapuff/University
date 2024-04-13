#pot totul in Hristos care ma intareste
from repository.repo import *
from service.service import *
from ui.consola import *

repo_ui=repository("read_me.txt")
serv=service_seriale(repo_ui)
ui=consola(serv)

ui.main()
