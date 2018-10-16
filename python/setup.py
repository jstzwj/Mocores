#-*- coding:utf-8 -*-

from setuptools import setup, find_packages

setup(
    name = "mocores",
    version = "0.1.1",
    keywords = ("pip", "actor-model", "cloud-computing", "distributed-systems"),
    description = "A distributed, high-scale computing system",
    long_description = "A distributed, high-scale computing system",
    license = "MIT Licence",

    url = "https://github.com/toyteam/Mocores",
    author = "JasonWang",
    author_email = "jstzwj@aliyun.com",

    packages = find_packages(),
    include_package_data = True,
    platforms = "any",
    install_requires = [""]
)