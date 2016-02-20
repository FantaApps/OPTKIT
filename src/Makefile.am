noinst_HEADERS=list.h node.h CrimeSTModel.h STModel.h csr.h truss.h
bin_PROGRAMS=optkit
optkit_SOURCES=main.cpp CrimeSTModel.cpp csr.cpp truss.cpp 
optkit_LDADD=$(OPENMP_LIBi) ../libs/liboptkit.la 
if DEBUG
AM_CXXFLAGS = -g  -I$(top_srcdir)/libs -D__USE_XOPEN2K8 -lglog -std=c++11 -Wall 
else
AM_CXXFLAGS = -g -I$(top_srcdir)/libs -DUSE_DEBUG -D__USE_XOPEN2K8 -lglog -std=c++11 -Wall 
endif
