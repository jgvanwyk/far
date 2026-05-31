# far

A Mac utility that resolves Finder aliases on the command-line.

## Usage

To use __far__, invoke it on the command-line with a file name:

>__far__ *file*

If  *file* names a Finder alias, then __far__ resolves it and displays the resulting path.

## Building

As a prerequisite, you need either [Xcode](https://developer.apple.com/xcode/) or the [Xcode command-line tools](https://developer.apple.com/documentation/xcode/installing-the-command-line-tools/) installed.
To build __far__, run “make”.

## Installation

To install __far__ into /usr/local, run “make install”, and to uninstall it, run “make uninstall”.
To install or uninstall __far__ using a different directory, assign the directory path to the PREFIX environment variable before running the previous commands.