import os
import setuptools
from subprocess import call
from distutils.command.build import build
from setuptools.command.install import install


class CustomBuild(build):
    def run(self):
        build.run(self)
        build_path = os.path.abspath(self.build_temp)
        base_path = os.path.dirname(__file__)
        c_src_path = os.path.join(base_path, 'c_src')
        cmd = ['make', 'OUT={}'.format(build_path), 'lib']

        def compile():
            call(cmd, cwd=c_src_path)

        self.mkpath(self.build_temp)
        self.execute(compile, [], 'Building liblyon')
        self.mkpath(self.build_lib)
        if not self.dry_run:
            target = os.path.join(build_path, 'liblyon.so')
            self.copy_file(target, os.path.join(self.build_lib, 'lyon'))


with open("README.md", "r") as fh:
    long_description = fh.read()


setuptools.setup(
    name="lyon",
    version="1.0.0",
    maintainer="Dmytro Tkanov",
    maintainer_email="dtkanov@sciforce.solutions",
    license='Apache License 2.0',
    description="Python port of Lyon's model from AuditoryToolbox",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/sciforce/lyon",
    packages=setuptools.find_packages(),
    include_package_data=True,
    install_requires=['numpy'],
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: Apache Software License",
        "Operating System :: POSIX :: Linux",
        "Topic :: Multimedia :: Sound/Audio",
    ],
    cmdclass={'build': CustomBuild}
)
