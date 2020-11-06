#!/usr/bin/env python3

from buildsystem import *
import sys

def mkdirs_allow_exist(dir):
    if not os.path.isdir(dir):
        os.makedirs(dir)


build_folder="build/"+os.name;

if os.name == "nt":
    ext=".exe"

mkdirs_allow_exist(build_folder)
mkdirs_allow_exist(build_folder+"/obj")
mkdirs_allow_exist(build_folder+"/tmp")

if "--rebuild" in sys.argv or "-r" in sys.argv:
    set_rebuild(True)

if "--silent" in sys.argv or "-s" in sys.argv:
    set_silent_verbose(True,False)

if "--verbose" in sys.argv or "-v" in sys.argv:
    set_silent_verbose(False,True)

ext=""

defines_cpp=[
    
]

flags_cpp=[
    "-Wall","-Iinclude","-O2","-fexceptions","-std=c++17","-Wold-style-cast","-Werror=return-type"
]

get_files(
    #source folder
    "src",
    #obj output folder
    build_folder+"/obj",
    #build temp folder
    build_folder+"/tmp",
    #extension <-> compiler association
    {
        ".cpp":gcc_cpp(defines_cpp,flags_cpp),
    },
    [
        "test"
    ],
    #linker
    linker_gcc(
        True,
        #flags
        ["-Llib","-s"],
        #libraries
        [],
        [],
        []
    )
).compile(build_folder+"/Interpreter"+ext)

get_files(
    #source folder
    "src",
    #obj output folder
    build_folder+"/obj",
    #build temp folder
    build_folder+"/tmp",
    #extension <-> compiler association
    {
        ".cpp":gcc_cpp(defines_cpp,flags_cpp),
    },
    [
        "main"
    ],
    #linker
    linker_gcc(
        True,
        #flags
        ["-Llib","-s"],
        #libraries
        [],
        [],
        []
    )
).compile(build_folder+"/Test"+ext)
