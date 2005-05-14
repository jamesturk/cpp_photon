#This file is part of Photon (http://photon.sourceforge.net)
#Copyright (C) 2004-2005 James Turk
#
# Author:
#  James Turk (jpt2433@rit.edu)
#
# Version:
#  $Id: SConstruct,v 1.8 2005/05/14 02:16:42 cozman Exp $

import os,os.path
import glob

def buildSuperHeader(self):
    header = file('include/'+LIBRARY+'.hpp','w')
    incGuard = string.upper(LIBRARY)+'_HPP'
    header.write('#ifndef '+incGuard+'\n')
    header.write('#define '+incGuard+'\n\n')
    for inc in INC_FILES:
        header.write('#include "'+inc+'"\n')
    header.write('\n#endif // '+incGuard+'\n')
    
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
            'mac':('GL','GLU','openal') }
try:
    OGL_LIB,GLU_LIB,OAL_LIB = libsMap[os.name]
except KeyError:
    print """Building on this platform (' + os.name + ') is not 
             supported.  Contact James (jpt2433@rit.edu) to check on
             support."""
    Exit(1)

# Configure the environment (Check libraries):
env = Environment(ENV = os.environ)
conf = Configure(env)
if not conf.CheckLibWithHeader(OAL_LIB, 'AL/al.h', 'C++'):
    print 'OpenAL not found, exiting.'
    Exit(1)
if not conf.CheckLibWithHeader(OGL_LIB, 'GL/gl.h', 'C++'):
    print 'OpenGL not found, exiting.'
    Exit(1)
if not conf.CheckLibWithHeader(GLU_LIB, 'GL/glu.h', 'C++'):
    print 'GLU not found, exiting.'
    Exit(1)
if not conf.CheckLibWithHeader('glfw', 'GL/glfw.h', 'C++'):
    print 'GLFW not found, exiting.'
    Exit(1)
env = conf.Finish()

# Define Builds:
BuildDir('build', 'src', duplicate=0)

lib = env.Library(os.path.join('lib',LIBRARY), source=SRC_FILES, 
            CPPPATH = 'include', CPPFLAGS = '-Wall -pedantic -O3') 
env.Alias(LIBRARY,lib)
env.Default(LIBRARY)

ndoc = env.Command('docs/index.html', './include',
    """NaturalDocs -nag -i $SOURCES -o HTML ./docs -p ./ndoc""")
env.Alias("docs",ndoc)

