#!/bin/bash

# This file is part of Photon (http://photon.sourceforge.net)
# Copyright (C) 2004-2005 James Turk
#
# Author:
#  James Turk (jpt2433@rit.edu)
#
# Version:
#  $Id: release.sh,v 1.2 2005/08/17 17:39:49 cozman Exp $

major=0
minor=1
release=0
suffix="-RC1"

cvsTag="release-${major}_${minor}_${release}${suffix}"
dirName="photon-${major}.${minor}"
srcPkgName="photon-${major}.${minor}.${release}${suffix}-src.tar.bz2"

# procedure to abort on errorcodes
check_errs()
{
  # Parameter 1 is the return code
  # Parameter 2 is text to display on failure.
  if [ "${1}" -ne "0" ]; then
    echo "ERROR : ${2}"
    # as a bonus, make our script exit with the right error code.
    exit ${1}
  fi
}

# pre mode is run when preparing for a release
if [[ "${1}" = "pre" ]]; then
    # first checkout a fresh copy from CVS
    echo "Attempting to check fresh copy of photon out from CVS..."
    rm -rf ./photon
    cvs -z3 -d:ext:cozman@cvs.sourceforge.net:/cvsroot/photon co -P photon
    check_errs $? "Obtaining photon via CVS failed"

    cd photon
    check_errs $? "No photon directory?! Cannot proceed."

    # run all scons targets
    scons
    check_errs $? "Building photon library failed, aborting."
    scons tests
    check_errs $? "Building photon tests failed, aborting."
    scons docs
    check_errs $? "Building photon docs failed, aborting."
    echo "All scons tests succeeded!"
    
    echo "\nTime for some sanity checks, then run release.sh"
    
elif [[ "${1}" = "release" ]]; then
    # first checkout a fresh copy from CVS
    echo "Attempting to check fresh copy of photon out from CVS..."
    rm -rf ./photon
    cvs -z3 -d:ext:cozman@cvs.sourceforge.net:/cvsroot/photon co -P photon
    check_errs $? "Obtaining photon via CVS failed"

    cd photon
    check_errs $? "No photon directory?! Cannot proceed."

    echo "Tagging current CVS as ${cvsTag}"
    cvs rtag ${cvsTag} photon
    check_errs $? "Tagging photon in CVS failed"
        
    echo "Attempting to export ${cvsTag} tagged copy of photon"
    rm -rf ./photon
    cvs -z3 -d:ext:cozman@cvs.sourceforge.net:/cvsroot/photon export -r ${cvsTag}  photon
    check_errs $? "${cvsTag} export failed"

    cd photon
    check_errs $? "No photon directory?! Cannot proceed."
    
    scons docs
    check_errs $? "Building photon docs failed, aborting."

    # remove non-essential files
    
    # rename directory for packaging
    cd ..
    mv photon ${dirName}
    tar cjf ${srcPkgName} ${dirName}/ 
    check_errs $? "Failed to create source package."
    
    echo "Automated portion of release complete, put it up on sourceforge and relax."
else
    echo "Usage: ./release.sh {pre|release}"
fi

exit
