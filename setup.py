from setuptools import setup, Extension
from Cython.Build import cythonize
import os

# para pegar todos os .c, .cpp do ./src mais facilmente
source_files = ["./src/aux.cpp", "./src/matrix.cpp", "./src/index.pyx"]

module = [
    Extension(
        name="npc",
        sources=source_files
    )
]

setup(
    name='npc',
    ext_modules=cythonize(module)
)
