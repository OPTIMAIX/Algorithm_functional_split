import os
import pandas as pd
import shutil
import json
import matplotlib.pyplot as plt
import numpy as np


scenario='scenario3_serv2'
level='4'
fich=open('./config/' + scenario + '.json')   #Config.json, escenario2.json, escenario3.json

data=json.load(fich)
fich.close()

fich=open('./config/aux_scen.json', 'w')
json.dump(data, fich)

fich.close()
iter=0

resPath = 'Results'
cmd = f'mkdir {resPath}' 
os.system(cmd)

os.system("./waf mode=debug")

for iteracion in np.arange(10, 20, 10):
    print('++++++++++++++++++++++++++++++++++ General iteration ', iter, '++++++++++++++++++++++++++++++++++++')
    fich=open('./config/aux_scen.json')
    data=json.load(fich)
    fich.close()
    ids=[]
    data['FS']=int(level)
    for i in data['BS']:
        ids.append(i['id'])
    fich=open('./config/aux_scen.json', 'w')
    json.dump(data, fich)
    fich.close()
    os.system(f'./waf') 
    jsonFile = './config/aux_scen.json'
    program = f'./programs/debug/main'
    cmd = f'{program} {jsonFile}'
    print(f'Calling {cmd}')
    os.system(cmd)
    for contador in range(len(ids)):
        path_origen='./' + ids[contador] + '_resources.txt'
        path_destino=f'./{resPath}/' + ids[contador] + '_resources_iter' + str(iter) + '_' + scenario + '_level' + level + '.txt'
        shutil.copyfile(path_origen, path_destino)

        path_origen='./' + ids[contador] + '_split.txt'
        path_destino=f'./{resPath}/' + ids[contador] + '_split_iter' + str(iter) + '_' + scenario + '_level' + level + '.txt'
        shutil.copyfile(path_origen, path_destino)
    
    path_origen='./Results_virtualQueue.txt'
    path_destino=f'./{resPath}/Results_virtualQueue_iter' + str(iter) + '_' + scenario + '_level' + level + '.txt'
    shutil.copyfile(path_origen, path_destino)

    path_origen='./Results_remResourcesPhysicalBs.txt'
    path_destino=f'./{resPath}/Results_remResourcesPhysicalBs_iter' + str(iter) + '_' + scenario + '_level' + level + '.txt'
    shutil.copyfile(path_origen, path_destino)

    path_origen='./Results_SINR.txt'
    path_destino=f'./{resPath}/Results_SINR_iter' + str(iter) + '_' + scenario + '_level' + level + '.txt'
    shutil.copyfile(path_origen, path_destino)

    path_origen='./Results_throughput.txt'
    path_destino=f'./{resPath}/Results_throughput_iter' + str(iter) + '_' + scenario + '_level' + level + '.txt'
    shutil.copyfile(path_origen, path_destino)

    iter=iter+1
print('Clean results files...')    
os.system('rm BS*_resources.txt')  
os.system('rm BS*_split.txt')  
os.system('rm Results_*.txt')  
