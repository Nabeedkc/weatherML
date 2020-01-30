import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn import linear_model

data = pd.read_csv("weather_data.csv", delimiter=',')

yxy=data['Temperature  [2 m above gnd]'].values
xyx=data['Sl'].values

xyx=np.reshape(xyx, (-1,1))
yxy=np.reshape(yxy, (-1,1))
model = linear_model.LinearRegression()
model.fit(xyx,yxy)
ypy = model.predict(xyx)
plt.scatter(xyx,yxy)
plt.plot(xyx,ypy, color='red')
plt.show()