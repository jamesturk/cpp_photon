# Photon release script

#!/bin/bash

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
    echo "release mode not implemented"

else
    echo "Usage: ./release.sh {pre|release}"
fi

exit
