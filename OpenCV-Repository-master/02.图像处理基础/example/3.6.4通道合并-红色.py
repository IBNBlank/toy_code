# -*- coding: utf-8 -*-
"""
Created on Wed May  9 09:35:10 2018

@author: Administrator
"""
import cv2
import numpy as np
a=cv2.imread("image\lenacolor.png")
rows,cols,chn=a.shape
b = np.zeros((rows,cols),dtype=a.dtype)  
g = np.zeros((rows,cols),dtype=a.dtype)  
r = cv2.split(a) [2]
m = cv2.merge([b,g,r])
cv2.imshow("merge",m)
cv2.waitKey()
cv2.destroyAllWindows()

