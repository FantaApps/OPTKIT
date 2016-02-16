##### trying to make
if [ "$(uname)" == "Darwin" ]; then
    glibtoolize
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    libtoolize
fi
aclocal
autoconf
automake -a
./configure
sudo ldconfig
