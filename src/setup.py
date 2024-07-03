from setuptools import setup, Extension
from Cython.Build import cythonize
import os

# para pegar todos os .c, .cpp do ./src mais facilmente
source_files = []
for root, dirs, files in os.walk("./"):
    for i in files:
        source_files.append(i)

module = [
    Extension(
        "npc",
        sources=source_files,
        language="c++"
    )
]

setup(
    name='npc',
    version='1.0',
    description='Clone de numpy',
    ext_modules=cythonize(module)
)
