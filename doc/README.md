# MIDI message parser documentation

This is not an [official version](https://github.com/BinaryNate/midi-message-parser) of MIDI message parser. It is an experimental fork by [6r1d](https://github.com/6r1d).
The API will change from time to time and library will be improving.

This is a file [GitHub](http://github.com/) should display by default, so the users can build the documentation.

## Skimming through the docs

(*You can try* to browse RST files using GitHub, but you won't have the same highlight, search index and theme.)

## Prerequisites

The documentation is written using [Sphinx](https://www.sphinx-doc.org/en/master/) documentation generator.
It allows you to have a better markup and document things faster, plus it adds code search function.

To build the documentation you'll need [Python 3](https://www.python.org/) package installed in your system.
You should also have Python's PIP tool to install Python libraries.

From that point on, you can install Sphinx by typing: `pip install -U Sphinx`.

## Building the documentation

Just go to "doc" directory and type: `make html`.

The HTML documentation will be located in `doc/_build` directory.
