noinst_PROGRAMS = graphutiltest 
graphutiltest_SOURCES=gt_graph_util.cpp ../src/graph_util.cpp
TESTS=graphutiltest

if DEBUG
AM_CXXFLAGS = -g  -fopenmp -I$(top_srcdir)/src -I/usr/local/include -D__USE_XOPEN2K8 -lgtest_main -lgtest -lboost_graph 
else
AM_CXXFLAGS = -g -fopenmp -I$(top_srcdir)/src -I/usr/local/include -DUSE_DEBUG -D__USE_XOPEN2K8 -lgtest_main -lgtest -lboost_graph
endif
