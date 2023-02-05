

from turtle import color
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import matplotlib.gridspec as gridspec


from base64 import encode
from cmath import exp, sin
from email.header import decode_header
from os import X_OK
import random
import re
from typing_extensions import Self
from xml.dom.minidom import ReadOnlySequentialNamedNodeMap
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import cv2
import imageio.v2 as imageio
from functools import cmp_to_key


x = np.linspace(0,4,1000)
y1 = -(x-2)*(x-2)
y2 = x*np.sin(x*x)*np.exp(np.cos(x))


plt.plot(x,y1,label = 'f(x) = -(x-2)$^{2}$',linewidth = 3)
plt.plot(x,y2,label = 'g(x) = xsin(x$^{2})$e$^{cosx}$',linewidth = 3)
plt.title('Function image to be optimized',fontsize=15, fontname="Times New Roman")
plt.xlabel('x', fontsize=14, fontname="Times New Roman")
plt.ylabel('y', fontsize=14, fontname="Times New Roman")
plt.legend()
plt.grid(True)
plt.show()