allumette
=========

Software for astrophotographic image registration and stacking

Design Ideas
============

The main work of doing the registration and stacking should be done by a
library, and we then provide interfaces to that library: a commandline
client for scripting, and a user-friendly gui frontend.

The configuration for the registration and stacking will be in JSON
files; clients will pass a JSON-encoded configuration to the library.

Doing the work
--------------

* `libraw` for reading raw files
* Eigen3 for doing the math
* Qt to make the C++ programming nicer


