#!/bin/bash
base_dir=`pwd`
pushd plugins/evernote
make $@ -j8
cp libevernote.a ${base_dir}/Libs/
popd

pushd third_party/sundown
make $@ -j8
cp libsundown.a ${base_dir}/Libs/
popd