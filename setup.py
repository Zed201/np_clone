from setuptools import setup, Extension
from Cython.Build import cythonize
import os

# para pegar todos os .c, .cpp do ./src mais facilmente
source_files = []
for root, dirs, files in os.walk("./src"):
    for i in files:
        source_files.append("./src/" + i)

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
