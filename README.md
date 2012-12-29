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

TODO
====

*   We need to implement the loading and decoding of RAW files. LibRaw
    will do the work of decoding and loading; the main issue here is
    wrapping it and deciding how we wish to store our data in memory. I
    suggest storing each pixel as four 32bit floats (RGBA) so that each
    pixel fits into a 128bit SSE register. We probably won't use the
    alpha channel, but the data alignment is important for speed.

*   We should probably implement a paging system. At first we can just
    ignore this, use as much memory as we please, and let Linux figure
    it out. But: 16 MP * 128 bpp = 244 MB per image, so 50 images means
    12 GB of memory. Not everyone has that much ram+swap, and some other
    operating systems are not known for paging sensibly.

    This should be done -- but later.

*   We need to implement a stacker which takes a list of images and
    collapses them into a single image via some particular algorithm,
    like average, median, kappa-sigma, etc. This should be
    general-purpose: we can use it for combining the dark, flat, bias,
    etc frames. Care should be taken in implementation to ensure memory
    locality: the different images will be all over the memory space,
    and so if we read a pixel from each, we're likely to have a lot of
    cache misses and bad performance. We need to have some kind of
    buffer that rearranges the data so that the pixel values from all of
    the images are stored next to each other.

    One thing to decide is whether or not to have the stacker
    allow for transformations of the image. We will need to do this for
    the light frames, but not for the other types of frames. Perhaps do
    this seperately? In that case:

    *   Implement an image transform which we can then apply to each
        light frame before we stack them.

*   We need to implement image registration. This has two parts to it:

    *   Star detection: picking out the stars in an image, based on some
        particular threshold.
    *   Alignment: once we have these stars, calculating the
        transformations to align them. There are algorithms
        [here](http://lear.inrialpes.fr/pubs/2004/MR04/)
        and
        [here](http://adsabs.harvard.edu/cgi-bin/nph-bib_query?bibcode=1995PASP..107.1119V&db_key=AST&high=39463d35aa24090)
        which do this job.
        
        Update: it seems that something along these lines may be built
        [into Eigen](http://eigen.tuxfamily.org/dox/group__Geometry__Module.html#gab3f5a82a24490b936f8694cf8fef8e60).

*   We need to implement creation of the master offset file from the
    dark frames, bias frames, and flat frames. Then we subtract this
    to get the result.

I think that that should produce some kind of minimally functional
application; we can worry about the user interface afterwards.


