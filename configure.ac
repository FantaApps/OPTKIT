AC_INIT([optkit], 1.0)
AM_INIT_AUTOMAKE
AC_PROG_CXX(g++-4.8.1 g++-4.8 g++-4.9 g++)

CXXFLAGS=
#debug related
AC_ARG_ENABLE(debug,
AS_HELP_STRING([--enable-debug],
               [enable debugging, default: no]),
	       [case "${enableval}" in
	              yes) debug=true ;;
		      no)  debug=false ;;
		      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
	       esac],
	      [debug=false])
AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")

#for libraries
LT_INIT

AC_CONFIG_FILES(Makefile libs/Makefile test/Makefile src/Makefile)
AC_OUTPUT
