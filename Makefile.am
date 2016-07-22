# Stop autoconf looking for readme file
AUTOMAKE_OPTIONS = foreign

# M4 Macros
ACLOCAL_AMFLAGS = -I ./m4 

AM_LDFLAGS =  $(AM_LFLAGS) -fopenmp

AM_CPPFLAGS = -I include/

readgmsh_LDADD = $(VORO_LDFLAGS)

# Main Program 
bin_PROGRAMS 	 = readgmsh

readgmsh_SOURCES =  src/element.cc \
            		    src/settings.cc \
                    src/mesh.cc \
		                src/main.cc
