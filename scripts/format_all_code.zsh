#!/bin/zsh

function dfs_dir() {
    echo scanning $1

    for file in $(echo $1"/"*.cpp) + $(echo $1"/"*.cc) + $(echo $1"/"*.h) + $(echo $1"/"*.hpp); do
        if [ -f "$file" ]; then
            echo formatting $file
            clang-format -i $file
        fi
    done

    for file in $(ls $1); do
        if [ -d $1"/"$file ]; then
            dfs_dir $1"/"$file
        fi
    done
}

dfs_dir $(pwd)
