#!/usr/bin/env python
# vim: set fileencoding=utf-8 :
# Andre Anjos <andre.anjos@idiap.ch>
# Thu 20 Sep 2012 14:43:19 CEST

"""Bindings for Liu's optical flow
"""

from setuptools import setup, find_packages, dist
dist.Distribution(dict(setup_requires=['xbob.blitz']))
from xbob.blitz.extension import Extension

version = '2.0.0a0'
packages = [
    'bob-core >= 1.2.2',
    'bob-sp >= 1.2.2',
    ]

setup(

    name="xbob.ip.optflow.hornschunck",
    version=version,
    description="Python bindings to the optical flow framework of Horn & Schunck",
    license="GPLv3",
    author='Andre Anjos',
    author_email='andre.anjos@idiap.ch',
    long_description=open('README.rst').read(),
    url='https://github.com/bioidiap/xbob.ip.optflow.hornschunck',

    packages=find_packages(),
    include_package_data=True,
    zip_safe=False,

    namespace_packages=[
      "xbob",
      "xbob.ip",
      "xbob.ip.optflow",
      ],

    install_requires=[
      'setuptools',
      'xbob.blitz',
      'xbob.io',
      'xbob.ip.color',
      'scipy', #for testing
    ],

    ext_modules = [
      Extension("xbob.ip.optflow.hornschunck.version",
        [
          "xbob/ip/optflow/hornschunck/version.cpp",
          ],
        packages = packages,
        version = version,
        ),
      Extension("xbob.ip.optflow.hornschunck._library",
        [
          "xbob/ip/optflow/hornschunck/SpatioTemporalGradient.cpp",
          "xbob/ip/optflow/hornschunck/HornAndSchunckFlow.cpp",
          "xbob/ip/optflow/hornschunck/forward.cpp",
          "xbob/ip/optflow/hornschunck/central.cpp",
          "xbob/ip/optflow/hornschunck/vanilla.cpp",
          "xbob/ip/optflow/hornschunck/flow.cpp",
          "xbob/ip/optflow/hornschunck/main.cpp",
          ],
        packages = packages,
        version = version,
        ),
      ],

    classifiers = [
      'Development Status :: 4 - Beta',
      'Intended Audience :: Developers',
      'License :: OSI Approved :: GNU General Public License v3 (GPLv3)',
      'Natural Language :: English',
      'Programming Language :: Python',
      'Programming Language :: Python :: 3',
      'Topic :: Scientific/Engineering :: Artificial Intelligence',
      'Topic :: Scientific/Engineering :: Image Recognition',
      ],

    )
