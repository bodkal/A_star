import csv
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
x=1000
obs=np.array([[0,0]])
path=np.array([[0,0]])
path1=np.zeros((1,x))
i=0

with open('board.csv', newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
    for row in spamreader:
        i += 1
        j=0
        for k in row:
            k=k.replace(' ', '')
            j+=1;
            if(k=='-500'):
                path=np.append(path,np.array([[i,j]]),axis=0)
            elif(k=='-100' ):
                obs =np.append(obs, np.array([[i, j]]),axis=0)



plt.plot(obs[1:,0],x-obs[1:,1],'s')
plt.plot(path[1:,0],x-path[1:,1],'s')
# plt.show()

with open('board.csv', newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
    for row in spamreader:
        a=np.fromstring(",".join(row).replace(' ', ''), dtype=np.float, sep=',')
        path1 = np.append(path1,np.array([a]), axis=0)




fig = plt.figure()

ax = fig.add_axes([0.1,0.1,0.6,0.8])
i = ax.imshow(path1.T, cmap ='Spectral', aspect='auto', interpolation='nearest')
colorbar_ax = fig.add_axes([0.7, 0.1, 0.1, 0.8])
fig.colorbar(i, cax=colorbar_ax)

plt.show()


