#!/bin/bash

cd "$WORKSPACE_ROOT"
clear
set -ex

# clean up

git clean -dxf
git reset --hard HEAD

# autoreconf setup

# touch ./AUTHORS ./ChangeLog ./NEWS ./README ./COPYING

if [ -f "./configure.in" ]; then
    mv ./configure.in ./configure.ac
fi

# autoreconf

# update config.guess and config.sub

# https://www.gnu.org/software/gettext/manual/html_node/config_002eguess.html
# wget -O config.guess 'https://git.savannah.gnu.org/gitweb/?p=config.git;a=blob_plain;f=config.guess;hb=HEAD'
# wget -O config.sub 'https://git.savannah.gnu.org/gitweb/?p=config.git;a=blob_plain;f=config.sub;hb=HEAD'

# configure and build

LOG_DIR="dev/logs"
mkdir -p ${LOG_DIR}

./autogen.sh > ${LOG_DIR}/autogen.log 2>&1

./configure --prefix=$WORKSPACE_ROOT/bin > ${LOG_DIR}/configure.log 2>&1

make -j4 > ${LOG_DIR}/make.log 2>&1

make install
