noinst_PROGRAMS = graphutiltest 
graphutiltest_SOURCES= gt_csr.cpp            ../src/csr.h        ../src/csr.cpp  \	   
					   gt_graph_util.cpp     ../src/bgl.h \
					   ../src/truss_plus.cpp ../src/truss_plus.h \
					   gt_truss.cpp          ../src/truss.h      ../src/truss.cpp \
					   gt_serialization.cpp  gt_main.cpp \
					   ../src/utils.h        ../src/utils.cpp    ../src/Stats.h \
					   ../src/Stats.cpp      ../src/Config.h     ../src/Config.cpp \
					   gt_stmodel.cpp        ../src/STModel.h    ../src/CrimeSTModel.h ../src/CrimeSTModel.cpp \ 
					   gt_core.cpp           ../src/core.h       ../src/core.cpp \ 
					   gt_dbscan.cpp         ../src/dbscan.h     ../src/dbscan.cpp \ 
                       ../libs/CSVparser.cpp ../libs/CSVparser.h test_util.h 
TESTS=graphutiltest

if DEBUG
AM_CXXFLAGS = -g  -L/lib64 -I$(top_srcdir)/src -I/usr/local/include -D__USE_XOPEN2K8 -lgtest_main -lgtest -DUSE_GTEST -lglog -std=c++11 -Wall -ljson_spirit -lboost_serialization -lpthread
else
AM_CXXFLAGS = -g -L/lib64 -I$(top_srcdir)/src -I/usr/local/include -DUSE_DEBUG -D__USE_XOPEN2K8 -lgtest_main -lgtest -DUSE_GTEST -lglog -std=c++11 -Wall -ljson_spirit -lboost_serialization -lpthread
endif
