import setuptools

with open("README.md", "r") as fh:
    long_description = fh.read()

setuptools.setup(
    name="lyon",
    version="1.0.0",
    author="Dmytro Tkanov",
    author_email="dtkanov@sciforce.solutions",
    description="Python port of Lyon's model from AuditoryToolbox",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/sciforce/lyon",
    packages=setuptools.find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: Apache Software License",
        "Operating System :: POSIX :: Linux",
        "Topic :: Multimedia :: Sound/Audio",
    ],
)
