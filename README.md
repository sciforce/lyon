[![Build Status](https://travis-ci.org/sciforce/lyon.svg?branch=master)](https://travis-ci.org/sciforce/lyon)

# Lyon's auditory model for Python
Python port of Lyon's model calculation from Auditory Toolbox.
Original version of Auditory Toolbox is written in C and MATLAB by Malcolm Slaney.

## Package contents
* Modified `soscascade.c`, `agc.c` and `sosfilters.c` (removed MEX-related part).
* `ctypes` wrapper for `soscascade()`, `agc()` and `sosfilters()` calls.
* Translation from MATLAB to Python for files necessary for successfull call to `LyonPassiveEar()`.

## Dependecies
If you plan to build manually and run tests, you'll need `libcheck` installed.
On Ubuntu 18.10 run:

``` bash
sudo apt-get install check
```

## Installation
### PIP

``` bash
pip install lyon
```

### Manual
Build a library and copy to installation location:

``` bash
make -C c_src lib
cp c_src/liblyon.so lyon/
```

you can verify that library is properly built by running a test suite:

``` bash
make -C c_src test
```

## Usage
The following code computes cochleogram for a sample sound:

``` python
from lyon import LyonCalc

calc = LyonCalc()
waveform, sample_rate = load('audio/file/path.wav')
decimation_factor = 64
coch = calc.lyon_passive_ear(waveform, sample_rate, decimation_factor)
print(coch.shape)
```

The code above should output shape of resulting auditory nerve response: `[<number of samples / decimation_factor>, 86]`.

See `examples/lyon_examples.py` for examples on running other functions.

## Links
* [AuditoryToolbox page](https://engineering.purdue.edu/~malcolm/interval/1998-010/)
* [Report describing function in toolbox](https://engineering.purdue.edu/~malcolm/interval/1998-010/AuditoryToolboxTechReport.pdf)
