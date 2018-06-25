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
import gensim.models.word2vec as w2v

warnings.filterwarnings(module='sklearn*', action='ignore', category=DeprecationWarning)

file = open("subt.txt","r")
sente = file.readlines()
sente = [word.split() for word in sente]




#sente =  sys.argv[1:]
vector = []
thrones2vec = w2v.Word2Vec.load("thrones2vec.w2v")
for sentence in sente:
        vector.append(np.mean([thrones2vec.wv[words.lower()] for words in sentence if words in thrones2vec] or [np.zeros(300)],axis=0))

fp = open("svm_trained","rb")
file_label = open("label_saved","rb")
clf = pickle.load(fp)
le = pickle.load(file_label)


predict = clf.predict(vector)
predicted = le.inverse_transform(predict)

ofile = open('label.txt','w')

for Emotion in predicted:
        ofile.write(Emotion)
        ofile.write('\n')



