#!/usr/bin/env python

from distutils.core import setup

setup(name='mocores',
      version='0.1',
      description='distributing computing framework',
      author='JunWang',
      author_email='jstzwj@aliyun.com',
      license="MIT",
      keywords="distributing",
      url='https://github.com/jstzwj/mocores.git',
      packages=['mocores',
            'mocores.core',],
      install_requires=[
            'lxml==4.3.3',
            'requests==2.21.0',
            'aiohttp==3.6.2'
      ],
     )