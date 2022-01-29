CFLAGS = ${shell pkgconf --cflags opencv4}
LDLIBS = ${shell pkgconf --libs opencv4}

% : %.cpp
	g++ ${CFLAGS} ${LDLIBS} -o $@ $<
