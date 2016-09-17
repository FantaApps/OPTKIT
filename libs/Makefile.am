noinst_LTLIBRARIES=liboptkit.la
liboptkit_la_SOURCES=CSVparser.cpp 
if DEBUG
liboptkit_la_CPPFLAGS = -O3  -fopenmp -I$(top_srcdir)/lib -D__USE_XOPEN2K8 -lglog -std=c++11
else
liboptkit_la_CPPFLAGS = -O3 -fopenmp -I$(top_srcdir)/lib -DUSE_DEBUG -D__USE_XOPEN2K8 -lglog -std=c++11
endif
