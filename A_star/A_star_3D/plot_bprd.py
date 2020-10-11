import csv
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D

obs=np.array([[0,0,0]])
path=np.array([[0,0,0]])
path1=np.zeros((1,500))
i=0



flag=1

with open('board.csv', newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
    for row in spamreader:
        a=np.fromstring(",".join(row).replace(' ', ''), dtype=np.float, sep=',')
        if(a[0]==-1):
            flag=0

        if(flag):
            obs = np.append(obs,np.array([a]), axis=0)
        else:
            path = np.append(path,np.array([a]), axis=0)



fig = plt.figure()

ax = fig.add_subplot(111, projection='3d')

xline = obs[1:,0]
yline = obs[1:,1]
zline = obs[1:,2]

ax.scatter(xline, yline, zline ,marker='s',s=30)

xline = path[2:,0]
yline = path[2:,1]
zline = path[2:,2]


ax.scatter(xline, yline, zline,marker='s',s=30)

plt.show()



