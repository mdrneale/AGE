# Engine 
ENGINEINCS=		-Isource/window 												\
				-Isource/io														\
				-Isource/graphics 												\
				-Isource/audio	 												\
				-Isource/geometry 												\
		    	-F/Library/Frameworks

ENGINELIBS=		-framework SDL2 				\
				-framework SDL2_image 			\
				-framework SDL2_mixer 			\
				-framework SDL2_ttf

ENGINEOBJS=		source/window/window.cpp		\
				source/window/mouse.cpp			\
				source/window/keyboard.cpp		\
				source/window/timer.cpp			\
				source/io/iohelper.cpp			\
				source/audio/audio.cpp			\
				source/audio/sound.cpp			\
				source/audio/music.cpp			\
				source/graphics/graphics.cpp	\
				source/graphics/texture.cpp		\
				source/graphics/font.cpp		\
				source/geometry/area.cpp		\
				source/geometry/point.cpp		\
				source/geometry/square.cpp

ENGINEOUT=		-o bin/libengine.dylib

ENGINE=	g++ $(ENGINEOUT) $(ENGINEINCS) $(ENGINELIBS) $(ENGINEOBJS) -dynamiclib


$(ENGINEOUT):	
	$(ENGINE)
	
