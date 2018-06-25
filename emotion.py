#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import sys
from sklearn.preprocessing import LabelEncoder
from sklearn.svm import LinearSVC
import numpy as np
import pickle
import os
import nltk
import warnings
warnings.filterwarnings(module='sklearn*', action='ignore', category=DeprecationWarning)



sente =  sys.argv[1:]
print("Presicted Emotion",sente)
thrones2vec = w2v.Word2Vec.load("thrones2vec.w2v")
vector = np.mean([thrones2vec.wv[words.lower()] for words in sente if words in thrones2vec] or [np.zeros(300)],axis=0)
fp = open("svm_trained","rb")
file_label = open("label_saved","rb")
clf = pickle.load(fp)
le = pickle.load(file_label)

newlist = ['1']
newlist[0] = vector

predict = clf.predict(newlist)
predicted = le.inverse_transform(predict)
print (predicted)
if predicted=='anger':
    sys.exit(3)
elif predicted=='joy':
    sys.exit(1)
elif predicted=='fear':
    sys.exit(4)
else:
    sys.exit(2)
