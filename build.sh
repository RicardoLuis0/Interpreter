#!/usr/bin/env bash

set -eu -o pipefail

if command -v RBuild &> /dev/null; then
    RBuild="RBuild"
else
    RBuild="./.RBuild"

    mkdir -p .deps
    need_run=true
    if [ -d ".deps/RBuild" ]; then
        echo "Updating RBuild"
        old_head=$(git -C .deps/RBuild rev-parse HEAD)
        git -C .deps/RBuild pull
        new_head=$(git -C .deps/RBuild rev-parse HEAD)
        if [ "$old_head" = "$new_head" ]; then
            need_run=false # don't try to compile if git hasn't updated
        fi
    else
        echo "Cloning RBuild"
        git -C .deps clone --depth=1 https://github.com/RicardoLuis0/RBuild
    fi

    if [ $need_run = true ]; then
        echo "Building RBuild"
        
        if command -v ./.deps/RBuild/build/lin/release/bin/RBuild &> /dev/null
        then
            cd .deps/RBuild
            ./build.sh
            cd ../..
        else
            cd .deps/RBuild
            ./build.sh
            ./build.sh
            cd ../..
        fi
    fi
    set +e
    command -v ./.RBuild &> /dev/null
    ok=$?
    set -e
    if [ $ok ]; then
        ln -srf .deps/RBuild/build/lin/release/bin/RBuild .RBuild
    fi
fi

$RBuild --file=BuildInterpreter.json "$@"