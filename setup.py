from setuptools import find_packages, setup, Extension

# read the contents of your README file
from pathlib import Path
this_directory = Path(__file__).parent
long_description = (this_directory / "README.md").read_text()

setup(
    name='othelloc',
    version='0.2.3',
    packages=['othelloc'],
    package_data={
        'othelloc': ['*.so'],
    },
    include_package_data=True,
    description='C library for Othello game',
    author='Hunter Livesay',
    license='MIT',
    long_description=long_description,
    long_description_content_type='text/markdown'
)