#This file is part of Photon (http://photon.sourceforge.net)
#Copyright (C) 2004-2005 James Turk
#
# Author:
#  James Turk (jpt2433@rit.edu)
#
# Version:
#  $Id: SConstruct,v 1.3 2005/03/02 08:46:45 cozman Exp $

import os,os.path
import glob
import string

subDirs = ['', 'audio', 'math', 'util', 'util/filesys', 'video']
libName = 'photon'

class Builder:   
    def __init__(self, subDirs):
        self.subDirs = subDirs
        self.srcDirs = self.combine('src',self.subDirs)
        self.incDirs = self.combine('include',self.subDirs)
        self.srcFiles = Flatten([self.getFiles(d, '*.cpp') 
                                for d in self.srcDirs])
        self.srcFiles = [f.replace('src','build') for f in self.srcFiles]
        self.incFiles = Flatten([self.getFiles(d, '*.hpp') 
                                for d in self.incDirs])
                                
    def getFilesRecursive(self, path, pat):
        files = glob.glob( os.path.join(path,pat) )
        for item in os.walk(path):
            basePath = item[0]
            for subdir in item[1]:
                files += glob.glob( os.path.join(basePath,subdir,pat) )
        return [modf.replace(path+os.sep, '').replace(os.sep,'/') for modf in files]

    def combine(self, prefix, dirs):
        """Add a prefix to all directories"""
        return [os.path.join(prefix,d) for d in dirs]

    def getFiles(self, path, pat):
        """Get all files which match a glob in a directory"""
        return glob.glob( os.path.join(path,pat) )
        
    def checkLibrary(self, name, lib, header):
        """Check if a library/header pair exists, report and bail if not"""
        if not self.conf.CheckLibWithHeader(lib, header, 'C++'):
            print name,'not found, exiting.'
            Exit(1)

    def checkDepends(self):
        """Check all the dependencies for the current project"""
        self.env = Environment(ENV = os.environ)
        self.conf = Configure(self.env)
        self.checkLibrary('OpenAL','OpenAL32','al.h')
        self.checkLibrary('OpenGL','opengl32','gl/gl.h')
        self.checkLibrary('GLFW','GLFW','glfw.h')
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
        
    def buildSuperHeader(self,libName):
        header = file('include/'+libName+'.hpp','w')
        incGuard = string.upper(libName)+'_HPP'
        header.write('#ifndef '+incGuard+'\n')
        header.write('#define '+incGuard+'\n\n')
        for inc in self.getFilesRecursive('./include','*.hpp'):
            header.write('#include "'+inc+'"\n')
        header.write('\n#endif // '+incGuard+'\n')
        
    def build(self):
        BuildDir('build', 'src', duplicate=0)
        self.checkDepends()

        self.namedBuild('photon', os.path.join('lib',libName), 'Library',
                        default=True,
                        source = self.srcFiles, CPPPATH = self.incDirs)
        self.buildSuperHeader(libName)
        ndoc = self.env.Command('docs/index.html', './include',
            """NaturalDocs -nag -i $SOURCES -o HTML ./docs -p ./ndoc""",
            target_factory=Dir)
        self.env.Alias("docs",ndoc)
        self.env.AlwaysBuild('docs/index.html')

    
b = Builder(subDirs)
b.build()
