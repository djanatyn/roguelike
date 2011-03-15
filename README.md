A Roguelike Project
===================
An experiment in the key of C
* * *

This is just a small project that I've been working on, and it may or may not be of interest to you. This is basically a small game in C, using the ncurses library, which utilizes ASCII characters as graphics. So far, this has mainly been an experiment with the library for me, but I've been making decent progress.

CURRENT STATE
-------------
The propgram currently includes an ascii character which can bump into the edges of your (80x24) terminal, will call you stupid if you press the wrong key, and will count the number of steps he takes. Consider it a score or something.

CONTROLS
--------
The game is easy to control (so far): Just use the default vim keybindings.

* left: h
* down: j
* up: k
* right: l

INSTALLATION
------------
The game has absolutely no dependencies besides ncurses. To compile, simple download main.c and the Makefile, and run "make". It should generate an executable "rogue" in the same directory. You don't even need root or anything.

Alternatively, you can navigate to the folder in which you downloaded main.c, and run "gcc main.c -o rogue -lncurses". Installation couldn't be easier.
