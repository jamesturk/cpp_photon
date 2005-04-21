#This file is part of Photon (http://photon.sourceforge.net)
#Copyright (C) 2004-2005 James Turk
#
# Author:
#  James Turk (jpt2433@rit.edu)
#
# Version:
#  $Id: SConstruct,v 1.7 2005/04/21 19:30:19 cozman Exp $

import os,os.path
import glob
import string


def combine(prefix, dirs):
    """Add a common prefix to all directories"""
    return [os.path.join(prefix,d) for d in dirs]

def getFiles(path, pat):
    """Get all files which match a glob in a directory"""
    return glob.glob( os.path.join(path,pat) )

def getFilesMulti(paths, pat):
    """Get all files which match a glob in a set of directories"""
    filelist = []
    for d in paths:
        filelist += getFiles(d, pat)
    return filelist

def getFilesRecursive(path, pat):
    files = glob.glob( os.path.join(path,pat) )
    for item in os.walk(path):
        basePath = item[0]
        for subdir in item[1]:
            files += glob.glob( os.path.join(basePath,subdir,pat) )
    return [modf.replace(path+os.sep, '').replace(os.sep,'/') for modf in files]

class Builder:   
    def __init__(self):
        self.libName = 'photon'
        self.subDirs = ['', 'audio', 'math', 'util', 'util/filesys', 'video']
        self.srcDirs = combine('src',self.subDirs)
        self.incDirs = combine('include',self.subDirs)
        self.srcFiles = getFilesMulti(self.srcDirs, '*.cpp')
        self.srcFiles = [f.replace('src','build') for f in self.srcFiles]
        self.incFiles = getFilesMulti(self.srcDirs, '*.hpp')

    def checkLibrary(self, name, lib, header):
        """Check if a library/header pair exists, report and bail if not"""
        if not self.conf.CheckLibWithHeader(lib, header, 'C++'):
            print name,'not found, exiting.'
            Exit(1)

    def checkDepends(self):
        """Check all the dependencies for the current project"""
        self.env = Environment(ENV = os.environ, 
                                LIBPATH=['/usr/lib', '/usr/local/lib'],
                                INCPATH=['/usr/include', '/usr/local/include'])
        self.conf = Configure(self.env)
        self.checkLibrary('OpenAL','openal','AL/al.h')
        self.checkLibrary('OpenGL','GL','GL/gl.h')
        self.checkLibrary('GLFW','glfw','GL/glfw.h')
        self.env = self.conf.Finish()
        
    def namedBuild(self, name, target, buildType, default=False, **extra):
        """Add a build target which can be addressed by name on the command line
            name      - Name to give to the target (using Alias)
            target    - Actual build target
            buildType - string describing what is being built (eg. Library, PDF)
            [default  - whether or not target is built by default (False)]
            **extra   - any options which should be given to the builder 
                        (eg. source='foo.c', CPPPATH='/foo/bar/baz')
            """
        # create a string with the desired buildType
        regStr = "self.env."+buildType+"(target = target, **extra)"
        # alias the build to the given name
        reg = self.env.Alias(name,  eval(regStr))
        if default:
            self.env.Default(reg)
        return reg
        
    def buildSuperHeader(self):
        header = file('include/'+self.libName+'.hpp','w')
        incGuard = string.upper(self.libName)+'_HPP'
        header.write('#ifndef '+incGuard+'\n')
        header.write('#define '+incGuard+'\n\n')
        for inc in getFilesRecursive('./include','*.hpp'):
            header.write('#include "'+inc+'"\n')
        header.write('\n#endif // '+incGuard+'\n')
        
    def build(self):
        BuildDir('build', 'src', duplicate=0)
        self.checkDepends()

        self.namedBuild('photon', os.path.join('lib',self.libName), 'Library',
                        default=True, 
                        source = self.srcFiles, CPPPATH = 'include',
                        CPPFLAGS = '-Wall -pedantic -pg')
        self.namedBuild('test00', 'test00', 'Program', default=False, 
                        source = 'test00.cpp', CPPPATH = self.incDirs, 
                        LIBPATH='./lib', 
                        LIBS=['photon','openal32','glfw','opengl32','glu32','physfs'],
                        CPPFLAGS = '-Wall -pedantic -pg', LINKFLAGS='-pg')
        self.buildSuperHeader()
        ndoc = self.env.Command('docs/index.html', './include',
            """NaturalDocs -nag -i $SOURCES -o HTML ./docs -p ./ndoc""")
        #self.env.Alias("docs",ndoc)
        self.env.AlwaysBuild('docs/index.html')

    
b = Builder()
b.build()
