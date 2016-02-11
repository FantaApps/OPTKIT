noinst_HEADERS=list.h node.h RTree.h CrimeSTModel.h STModel.h CSVparser.h 
bin_PROGRAMS=optkit
optkit_SOURCES=main.cpp CrimeSTModel.cpp CSVparser.cpp 
optkit_LDADD=$(OPENMP_LIBi) 
if DEBUG
AM_CXXFLAGS = -g  -fopenmp -I$(top_srcdir)/lib -D__USE_XOPEN2K8 -lglog -std=c++11
else
AM_CXXFLAGS = -g -fopenmp -I$(top_srcdir)/lib -DUSE_DEBUG -D__USE_XOPEN2K8 -lglog -std=c++11
endif
