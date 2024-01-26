import os
import pandas as pd

site = 'https://archive.ics.uci.edu/ml/'\
    'machine-learning-databases/iris/iris.data'
print('URL :', site)
df = pd.read_csv(site, header=None, encoding='utf-8')
df.to_csv('data.csv', index=False)