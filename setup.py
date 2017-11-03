# Cython wrapper for taskMain.cpp  
# Script for comparing the results between image captured
# and image edited.

from distutils.core import setup
from Cython.Build import cythonize
from libcpp.iostream cimport iostream
from libcpp.vector cimport vector

import Image

setup(ext_modules = cythonize(
	   # No user defined header file used, so cython source not specified
           sources=["taskMain.cpp"],  # additional source file(s)
           language="c++",            # generate C++ code
      ))

# Image is loaded using Image module 
# processImage is called with 
# a) original image
# b) edited image

ORIGINAL_IMAGE = Image.open("image.jpg")
EDITED_IMAGE = Image.open('editedImage.jpg')
cdef processImage(ORIGINAL_IMAGE)
cdef processImage(EDITED_IMAGE)
	

