# Solver for the game Lonpos Cosmic Creature.

![Demo solution](http://github.com/johannestoger/cc-solver/blob/master/problems/demo6.png?raw=true)

Game maker homepage: http://lonpos.cc/en/userGuideDownload_cc.php

## Dependencies:
* clang++ 3.1 or g++ 4.2
* Eigen 3.0, see http://eigen.tuxfamily.org

Code is tested on Ubuntu Linux 12.04 and Mac OSX 10.7.5.

## How to run:
1. Download Eigen 3.0. It's a C++ template library, so just unpack it in some directory.
1. Set the include path of Eigen in Makefile to the directory you unpacked Eigen into.
1. Run make
1. Run "./solver problems/demo5". The directory problems/ contains some different puzzles to run.

The program printpieces reads the piece definitions from the files in
gamedata/ and shows how they are numbered in the code.

## License
This code is released under the GNU General Public Licence v3 (see LICENSE).
