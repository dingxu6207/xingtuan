# -*- coding: utf-8 -*-
"""
Created on Tue Sep 22 09:09:58 2020

@author: dingxu
"""

import pandas as pd
import numpy as np

df = pd.read_csv('vizier_votable.tsv', sep = ';', encoding='gbk')

#df = pd.read_csv('NGC7142O.tsv', sep = ';', encoding='gbk')


dataframe = df.dropna()

#npgaia = dataframe.as_matrix()

#hang,lie = npgaia.shape

#print(dataframe.tail(6))

newdata = dataframe.values

hang,lie = newdata.shape

temp = []
for i in range(0,hang):
    try:
        data = np.float32(newdata[i])
        temp.append(data)
    except:
        print('it is error')
        
arraydata = np.array(temp)



np.savetxt('Gaiadata.txt', arraydata)
