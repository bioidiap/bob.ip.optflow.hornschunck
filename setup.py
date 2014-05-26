#!/usr/bin/env python
# vim: set fileencoding=utf-8 :
# Andre Anjos <andre.anjos@idiap.ch>
# Thu 20 Sep 2012 14:43:19 CEST

"""Bindings for Liu's optical flow
"""

from setuptools import setup, find_packages, dist
dist.Distribution(dict(setup_requires=['bob.blitz']))
from bob.blitz.extension import Extension

version = '2.0.0a0'
packages = [
    'bob-core >= 1.2.2',
    'bob-sp >= 1.2.2',
    ]

setup(

    name="bob.ip.optflow.hornschunck",
    version=version,
    description="Python bindings to the optical flow framework of Horn & Schunck",
    license="GPLv3",
    author='Andre Anjos',
    author_email='andre.anjos@idiap.ch',
    long_description=open('README.rst').read(),
    url='https://github.com/bioidiap/bob.ip.optflow.hornschunck',

    packages=find_packages(),
    include_package_data=True,
    zip_safe=False,

    namespace_packages=[
      "bob",
      "bob.ip",
      "bob.ip.optflow",
      ],

    install_requires=[
      'setuptools',
      'bob.blitz',
      'bob.io.base',
      'bob.ip.color',
      'scipy', #for testing
    ],

    ext_modules = [
      Extension("bob.ip.optflow.hornschunck.version",
        [
          "bob/ip/optflow/hornschunck/version.cpp",
          ],
        packages = packages,
        version = version,
        ),
      Extension("bob.ip.optflow.hornschunck._library",
        [
          "bob/ip/optflow/hornschunck/SpatioTemporalGradient.cpp",
          "bob/ip/optflow/hornschunck/HornAndSchunckFlow.cpp",
          "bob/ip/optflow/hornschunck/forward.cpp",
          "bob/ip/optflow/hornschunck/central.cpp",
          "bob/ip/optflow/hornschunck/vanilla.cpp",
          "bob/ip/optflow/hornschunck/flow.cpp",
          "bob/ip/optflow/hornschunck/main.cpp",
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
