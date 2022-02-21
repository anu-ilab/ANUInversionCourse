# rm -rf _skbuild; pip install -e .

import sys


try:
    from skbuild import setup
except ImportError:
    print(
        "Please update pip, you need pip 10 or greater,\n"
        " or you need to install the PEP 518 requirements in pyproject.toml yourself",
        file=sys.stderr,
    )
    raise

setup(
    name="ANU_inversion_course",
    version="0.1.0",

    description="ANU Inversion Course Package",
    author="InLab",
    packages=[
        "anu_inversion_course",
    ],
    install_requires=[
        "numpy>=1.22.0",
        "matplotlib>=3.5.0",
        "scipy>=1.7.0",
        "tqdm>=4.62.0",
        "seaborn>=0.11.0",
    ],
)
