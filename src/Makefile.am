noinst_HEADERS=list.h node.h CrimeSTModel.h STModel.h csr.h truss.h Stats.h Config.h utils.h bgl.h truss_plus.h core.h 
bin_PROGRAMS=optkit
optkit_SOURCES=main.cpp CrimeSTModel.cpp csr.cpp truss.cpp Stats.cpp Config.cpp utils.cpp truss_plus.cpp core.cpp
optkit_LDADD=$(OPENMP_LIBi) ../libs/liboptkit.la 
if DEBUG
AM_CXXFLAGS = -g  -I$(top_srcdir)/libs -D__USE_XOPEN2K8 -lglog -std=c++11 -Wall -ljson_spirit -lboost_serialization 
else
AM_CXXFLAGS = -g -I$(top_srcdir)/libs -DUSE_DEBUG -D__USE_XOPEN2K8 -lglog -std=c++11 -Wall  -ljson_spirit -lboost_serialization
endif
