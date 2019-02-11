import os
import setuptools
from subprocess import call
from distutils.command.build import build
from setuptools.command.install import install


class CustomBuild(build):
    def run(self):
        build.run()
        build_path = os.path.abspath(self.build_temp)
        base_path = os.path.dirname(__file__)
        c_src_path = os.path.join(base_path, 'c_src')
        cmd = ['make', 'OUT={}'.format(build_path), 'lib']

        def compile():
            call(cmd, cwd=c_src_path)

        self.execute(compile, [], 'Building liblyon')
        self.mkpath(self.build_lib)
        if not self.dry_run:
            target = os.path.join(build_path, 'liblyon.so')
            self.copy_file(target, self.build_lib)


class CustomInstall(install):
    def run(self):
        install.run(self)
        self.copy_tree(self.build_lib, self.install_lib)


with open("README.md", "r") as fh:
    long_description = fh.read()


setuptools.setup(
    name="lyon",
    version="1.0.0",
    maintainer="Dmytro Tkanov",
    maintainer_email="dtkanov@sciforce.solutions",
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
    cmdclass={'build': CustomBuild, 'install': CustomInstall}
)
