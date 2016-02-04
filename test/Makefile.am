noinst_PROGRAMS = graphutiltest 
graphutiltest_SOURCES= gt_csr.cpp ../src/csr.h  gt_truss.cpp ../src/truss.h test_util.h 
TESTS=graphutiltest

if DEBUG
AM_CXXFLAGS = -g  -fopenmp -I$(top_srcdir)/src -I/usr/local/include -D__USE_XOPEN2K8 -lgtest_main -lgtest -lboost_graph -DUSE_GTEST -lglog
else
AM_CXXFLAGS = -g -fopenmp -I$(top_srcdir)/src -I/usr/local/include -DUSE_DEBUG -D__USE_XOPEN2K8 -lgtest_main -lgtest -lboost_graph -DUSE_GTEST -lglog
endif
