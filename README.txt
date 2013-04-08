Qt Subsurface - An Open Source Port of the Subsurface Dive Log Application
--------------------------------------------------------------------------

At subsurface.hohndel.org you can find details of the original subsurface project
based on the GTK2+ graphics toolkit.

During development, several of the contributors to that project had issues
with GTK. At times of maximum frustration a move to Qt was proposed although
little clear intent was expressed. The aim of this project is to add a little
shove in that direction.

The Subsurface project has plenty of support from C-programmers but is lacking
in experience of the GUI side of things. A change of toolkit is seen as a big
job.

My own backgound is more in C++ than C and I have been exposed to Qt4 for some
time now. Whilst I won't claim a deep experience in Qt, I do enjoy using it
and am confident I can develop the main widgets a Qt-based version of Subsurface
to the point of making the switch from GTK to Qt a less daunting prospect.

A general outline of the direction of travel might look like this:

 * prototype dive list in model/view
 * prototype dive profile in suitable graphics widget
 * protoyype KDE/Marble based widget for location info
 * assemble the prototypes into MDI with QSettings etc.

I'm not at all sure at what point others might wish to join this effort. At some
level, that doesn't matter. I'm keen to play with items 1 & 2 above for my own
benefit and I've had some experience with items 3 & 4.  So even if this ends up
going nowhere, I'll have fun extending my experience. This also provides a useful
backdrop to exploring the boundaries between Qt4 and Qt5. It may also open up
some interesting possibilities to move from Linux/OSX/Win platforms onto other
form factors (e.g. through QML and support for e.g. Android).

If you have ideas or want to contribute, contact me.

DiveList
--------

The first element in the journey is the dive list. This is a simple model/view
implementation of QTreeview and QAbstractItemModel subclasses to present dives
in a navigable list. The Subsurface application has support for particular
keyboard driven functions and allows dives to be grouped into trips. The initial
commit of divelist doesn't yet do any of this. It just presents the subclasses
with the minimum of fuss as a place to start.  The code has been compiled and
has some basic exercise on Linx (openSUSE 12.2) with both Qt 4.8.1 and Qt 5.0.1.


DiveProfile
-----------

Next experiment here?


Marble
------

TBD


The Main Event
--------------

TBD

License: LGPLv2
[reference out etc...]

Amit Chaudhuri
amit.k.chaudhuri@gmail.com
