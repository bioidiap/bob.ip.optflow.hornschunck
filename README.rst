.. vim: set fileencoding=utf-8 :
.. Andre Anjos <andre.anjos@idiap.ch>
.. Tue  1 Apr 12:32:06 2014 CEST

.. image:: https://travis-ci.org/bioidiap/xbob.ip.optflow.hornschunck.svg?branch=master
   :target: https://travis-ci.org/bioidiap/xbob.ip.optflow.hornschunck
.. image:: https://coveralls.io/repos/bioidiap/xbob.ip.optflow.hornschunck/badge.png
   :target: https://coveralls.io/r/bioidiap/xbob.ip.optflow.hornschunck
.. image:: http://img.shields.io/github/tag/bioidiap/xbob.ip.optflow.hornschunck.png
   :target: https://github.com/bioidiap/xbob.ip.optflow.hornschunck
.. image:: http://img.shields.io/pypi/v/xbob.ip.optflow.hornschunck.png
   :target: https://pypi.python.org/pypi/xbob.ip.optflow.hornschunck
.. image:: http://img.shields.io/pypi/dm/xbob.ip.optflow.hornschunck.png
   :target: https://pypi.python.org/pypi/xbob.ip.optflow.hornschunck

============================================================
 Python Bindings to Horn & Schunck's Optical Flow Framework
============================================================

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

Installation
------------

Install it through normal means, via PyPI or use ``zc.buildout`` to bootstrap
the package and run test units.

Testing
-------

You can run a set of tests using the nose test runner::

  $ nosetests -sv xbob.ip.optflow.hornschunck

.. warning::

   If Bob <= 1.2.1 is installed on your python path, nose will automatically
   load the old version of the insulate plugin available in Bob, which will
   trigger the loading of incompatible shared libraries (from Bob itself), in
   to your working binary. This will cause a stack corruption. Either remove
   the centrally installed version of Bob, or build your own version of Python
   in which Bob <= 1.2.1 is not installed.

You can run our documentation tests using sphinx itself::

  $ sphinx-build -b doctest doc sphinx

You can test overall test coverage with::

  $ nosetests --with-coverage --cover-package=xbob.ip.optflow.hornschunck

The ``coverage`` egg must be installed for this to work properly.

Development
-----------

To develop this package, install using ``zc.buildout``, using the buildout
configuration found on the root of the package::

  $ python bootstrap.py
  ...
  $ ./bin/buildout

Tweak the options in ``buildout.cfg`` to disable/enable verbosity and debug
builds.

.. Place your references here:

.. _bob: http://www.idiap.ch/software/bob/
.. _opencv: http://opencv.org/
.. _horn & schunck: https://en.wikipedia.org/wiki/Horn%E2%80%93Schunck_method
