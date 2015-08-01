noinst_HEADERS=insknap.h insmed.h list.h timer.h insdis.h instance.h plist.h utils.h insmc.h listint.h factory.h config.h 
bin_PROGRAMS=optkit
optkit_SOURCES=insdis.cpp insmed.cpp plist.cpp timer.cpp insdis.h list.cpp insknap.cpp instance.cpp main.cpp utils.cpp insmc.cpp listint.cpp 
optkit_LDADD=$(OPENMP_LIBi) 
if DEBUG
AM_CXXFLAGS = -g  -fopenmp -I$(top_srcdir)/lib -D__USE_XOPEN2K8
else
AM_CXXFLAGS = -g -fopenmp -I$(top_srcdir)/lib -DUSE_DEBUG -D__USE_XOPEN2K8 
endif
