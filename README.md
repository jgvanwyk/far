# far

A Mac utility that resolves Finder aliases on the command line.

## Usage

To use __far__, invoke it at the command line with one or more Finder aliases:
```
far file...
```
__far__ will resolve each alias and display the resulting path.
For more information, consult the included manual page far(1).

## Installation

To install __far__, run `make` and `make install`, optionally providing a value for the PREFIX variable to determine the install location.
By default, PREFIX is /usr/local.
To uninstall __far__, run `make uninstall` with the same PREFIX value.