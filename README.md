Angry Birds copy made with c++

Used box2d 2d physics engine and Qt for graphics. CMake for building.



Running our project remotely:

    You can do the X11 forwarding in any way but we have been using XQuartz on mac.

    Open XQuartz 
    => ssh -XC username@lyta.aalto.fi
    => write your password
    => go to project directory (e.g. cd AngryBirds)
    => git fetch 
    => git checkout master 
    => git pull 
    => cd src 
    => mkdir build
    => cd build/
    => cmake ..
    => make
    => ./angry-birds 
    => should open our project

Another way: install qt5 open source and run/build from your local machine

    => go to project directory 
    => git fetch 
    => git checkout master 
    => git pull 
    => cd src 
    => mkdir build
    => cd build/
    => cmake ..
    => make
    => ./angry-birds
    => should open our project

NOTICE:
	using small window instead of fullscreen can improve performance/fps
