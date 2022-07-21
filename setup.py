# rm -rf _skbuild; pip install -e .

import sys
import pathlib

# import skbuild
try:
    from skbuild import setup
except ImportError:
    print(
        "Please update pip, you need pip 10 or greater,\n"
        " or you need to install the PEP 518 requirements in pyproject.toml yourself",
        file=sys.stderr,
    )
    raise

# get version number
_ROOT = pathlib.Path(__file__).parent
with open(str(_ROOT / '_version.py')) as f:
    for line in f:
        if line.startswith('__version__ ='):
            _, _, version = line.partition('=')
            VERSION = version.strip(" \n'\"")
            break
    else:
        raise RuntimeError(
            'unable to read the version from ./_version.py')

# run set up
setup(
    name="ANU_inversion_course",
    version=VERSION,

    description="ANU Inversion Course Package",
    author="InLab",
    packages=[
        "anu_inversion_course",
    ],
    install_requires=[
        "numpy>=1.18",
        "matplotlib>=3.3.0",
        "scipy>=1.0.0",
        "tqdm>=4.62.0",
        "seaborn>=0.11.0",
        "corner",
    ],
)
