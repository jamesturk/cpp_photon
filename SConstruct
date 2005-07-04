#This file is part of Photon (http://photon.sourceforge.net)
#Copyright (C) 2004-2005 James Turk
#
# Author:
#  James Turk (jpt2433@rit.edu)
#
# Version:
#  $Id: SConstruct,v 1.15 2005/07/04 03:06:06 cozman Exp $

import os,os.path
import glob
import string

def getFilesMulti(paths, pat):
    """Get all files which match a glob in a set of directories"""
    filelist = []
    for d in paths:
        filelist += glob.glob( os.path.join(d,pat) )
    return filelist

## config variables ##
LIBRARY = 'photon'
SUB_DIRS = ['', 'audio', 'math', 'util', 'util/filesys', 'video']
SRC_DIRS = ["src/%s" % d for d in SUB_DIRS]
INC_DIRS = ["include/%s" % d for d in SUB_DIRS]
SRC_FILES = [f.replace('src','build') for f in getFilesMulti(SRC_DIRS, '*.cpp')]
INC_FILES = getFilesMulti(INC_DIRS, '*.hpp')

libsMap = {
            'nt':('opengl32','glu32','openal32'),
            'posix':('GL','GLU','openal'),
            'mac':('GL','GLU','openal')}
try:
    OGL_LIB,GLU_LIB,OAL_LIB = libsMap[os.name]
except KeyError:
    print """Building on this platform (' + os.name + ') is not 
             supported.  Contact James (jpt2433@rit.edu) to check on
             support."""
    Exit(1)

# Configure the environment (Check libraries):
env = Environment(ENV = os.environ,
                    LIBPATH=['/usr/lib', '/usr/local/lib'],
                    INCPATH=['/usr/include', '/usr/local/include'],
                    CPPFLAGS = ['`freetype-config --cflags`', '-Wall', 
                                '-pedantic']
                    )
                    
# Define Builds:
BuildDir('build', 'src', duplicate=0)

lib = env.Library(os.path.join('lib',LIBRARY), source=SRC_FILES, 
            CPPPATH = 'include') 
env.Alias(LIBRARY,lib)
env.Default(LIBRARY)

ndoc = env.Command('docs/index.html', './include',
    """NaturalDocs -nag -i $SOURCES -o HTML ./docs -p ./ndoc""")
env.Alias("docs",ndoc)


# Tests:
tests = []
test_srcs = glob.glob( os.path.join('test', '*_test.cpp') )

for test_src in test_srcs:
    test_name = test_src.replace('_test.cpp','')
    tests.append(env.Program(test_name, source=test_src, CPPPATH = INC_DIRS+['/usr/include/freetype2/'],
                    LIBPATH='./lib', CPPFLAGS = '-Wall -pedantic', 
                    LIBS=['photon',OAL_LIB,'glfw',OGL_LIB,GLU_LIB,'physfs','corona','freetype']))
env.Alias('test',tests)


if LIBRARY in BUILD_TARGETS:    
    conf = Configure(env)
    if not conf.CheckLibWithHeader(OGL_LIB, 'GL/gl.h', 'C++'):
        print 'OpenGL not found, exiting.'
        Exit(1)
    if not conf.CheckLibWithHeader(GLU_LIB, 'GL/glu.h', 'C++'):
        print 'GLU not found, exiting.'
        Exit(1)
    if not conf.CheckLibWithHeader('glfw', 'GL/glfw.h', 'C++'):
        print 'GLFW not found, exiting.'
        Exit(1)
    if not conf.CheckLibWithHeader('freetype', 'ft2build.h', 'C++'):
        print 'Freetype2 not found, exiting.'
        Exit(1)    
    if not conf.CheckLibWithHeader('corona', 'corona.h', 'C++'):
        print 'Corona not found, exiting.'
        Exit(1)
    if conf.CheckLibWithHeader(OAL_LIB, 'zAL/al.h', 'C++'):
        conf.env.Append(CPPFLAGS='-DPHOTON_USE_OPENAL')
    else:
        print 'OpenAL not found, continuing without OpenAL support.'
    env = conf.Finish()

    # Build the Super-Header (only if this is a normal build)
    header = file('include/'+LIBRARY+'.hpp','w')
    incGuard = LIBRARY.upper()+'_HPP'
    header.write('#ifndef '+incGuard+'\n')
    header.write('#define '+incGuard+'\n\n')
    for inc in INC_FILES:
        header.write('#include "'+inc.replace('include/','')+'"\n')
    header.write('\n#endif // '+incGuard+'\n')
    header.close()
    print 'Built '+LIBRARY+'.hpp'


