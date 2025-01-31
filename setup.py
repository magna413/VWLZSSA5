from setuptools import setup, find_packages

setup(
    name="VW LZSS A5",
    version="1.0.0",
    author="Magnus Jaaska",
    author_email="",
    description="A custom LZSS compression library found in VW 2Q0 Lane Assist MFK3.0 Cameras.",
    long_description=open("README.md").read(),
    long_description_content_type="text/markdown",
    url="https://github.com/magna413/VWLZSSA5",
    packages=find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires=">=3.6",
)
