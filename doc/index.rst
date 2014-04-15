.. vim: set fileencoding=utf-8 :
.. Andre Anjos <andre.anjos@idiap.ch>
.. Thu  3 Apr 13:47:28 2014 CEST
..
.. Copyright (C) 2011-2014 Idiap Research Institute, Martigny, Switzerland

============================================================
 Python Bindings to Horn & Schunck's Optical Flow Framework
============================================================

.. todolist::

This package is a simple Python wrapper to an open-source Optical Flow
estimator based on the works by `Horn & Schunck`_::

    @article{Horn_Schunck_1981,
      author = {B.K.P. Horn and B.G. Schunck},
      title = {Determining optical flow},
      year = {1981},
      booktitle = {Artificial Intelligence},
      volume = {17},
      pages = {185--203},
    }

The implementation is purely based on `Bob`_::

    @inproceedings{Anjos_ACMMM_2012,
      author = {A. Anjos and L. El Shafey and R. Wallace and M. G\"unther and C. McCool and S. Marcel},
      title = {Bob: a free signal processing and machine learning toolbox for researchers},
      year = {2012},
      month = oct,
      booktitle = {20th ACM Conference on Multimedia Systems (ACMMM), Nara, Japan},
      publisher = {ACM Press},
      url = {http://publications.idiap.ch/downloads/papers/2012/Anjos_Bob_ACMMM12.pdf},
    }

This package also provides a unit testing framework, to check on the accuracy
of results produced in different platforms. The testing framework also requires
`OpenCV`_ for comparison purposes.

Documentation
-------------

.. toctree::
   :maxdepth: 2

   py_api

Indices and tables
------------------

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`

.. include:: links.rst

.. Place your references here:

.. _horn & schunck: https://en.wikipedia.org/wiki/Horn%E2%80%93Schunck_method
