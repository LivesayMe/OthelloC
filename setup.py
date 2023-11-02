from setuptools import find_packages, setup, Extension

setup(
    name='othelloc',
    version='0.2.0',
    packages=['othello'],
    package_data={
        'othello': ['*.so'],
    },
    include_package_data=True,
    description='C library for Othello game',
    author='Hunter Livesay',
    license='MIT',
)