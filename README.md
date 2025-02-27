# far

A small command line utility for the Mac that resolves Finder aliases.

To use `far`, invoke it at the command line with one or more file paths:
```sh
far file...
```
For each provided file path, if the path represents a Finder alias,
`far` will output the file path encoded by the alias.
