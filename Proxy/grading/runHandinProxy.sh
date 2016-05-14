#!/bin/bash
#
# Usage: $0 port andrewid
#
# This script helps streamline the process of grading the proxylab
# RealPages.  Given a port and an andrewid, it creates a grading
# directory named andrewid/, copies the student's most recent
# submission tarball to that directory, and then extracts, compiles,
# and run the proxy on the given port.  Hit ctrl-c to kill the proxy
# and exit the script.
#

# Error Handling:
# - Check to see if someone has started grading for said user.
#   - If ${dest} exists, everything is fine.
#   - If a proxylab-handin tarball has already been copied over to ${dest}
#     however, we do not want to overwrite what is already there, as any 
#     future grading should continue off of the existing tarball.
# - Check to see that said user has actually submitted a tarball to grade.
#
# 12/22: Updated by droh to "make clean" before making proxy.
#

#######################################
# TODO: CHANGE ME DEPENDING ON THE YEAR
#######################################
coursedir="/afs/cs/academic/class/15213-s16"


################## USAGE CHECK AND VARIABLE SETUP ##################
# Input Handling
if [[ $# -ne 2 ]]; then
  echo "Usage: $0 port andrewid"
  exit -1
fi

# Basic Global Variables for use throughout the script.
port=$1
id="$2@andrew.cmu.edu"
basedir="${coursedir}/autolab/proxylab"
src="${basedir}/handin"
dest="${basedir}/grading/${id}"

# Default colors - Used for output.
WHITE="\e[0m"
RED="\e[1;31m"
GREEN="\e[1;32m"
BLUE="\e[1;34m"

# 256 Color functions - Used for output.
function BOLD_EXT_COLOR () { echo -ne "\e[1;38;5;$1m"; }
ORANGE=`BOLD_EXT_COLOR 172`
SBLUE=`BOLD_EXT_COLOR 33`
MAGENTA=`BOLD_EXT_COLOR 126`

################## FUNCTIONS ##################

# Check if someone has already copied over a proxylab-handin.tar
checkGrading() {
  ls ${dest}/${id}_*_proxylab-handin.tar &> /dev/null;
  if [ $? -eq 0 ]; then
    copied=`ls ${dest}/${id}_*_proxylab-handin.tar`;
    echo -e "${WHITE}The following proxylab-handin.tar already exist in ${BLUE}${dest}${WHITE}:";
    echo -e "${RED}${copied}${WHITE}";
    exit -2;
  fi;
}

# Check to see if there were any submissions for said user.
checkHandin() {
  ls ${src}/${id}_*_proxylab-handin.tar &> /dev/null;
  if [ $? -ne 0 ]; then
    echo -e "There are no proxylab-handins for the user ${ORANGE}${id}${WHITE} in ${BLUE}${src}${WHITE}.";
    exit -3;
  fi;
}

# find the most recent submission. (Largest number submission)
# Make the grading directory if it already doens't exist.
# Copy over the tarball and extract it.
setupDirectory() {
  echo -e "${WHITE}Preparing grading directory for ${ORANGE}${id}${WHITE}."

  submissions=`ls ${src}/${id}_*_proxylab-handin.tar | sed 's/.*_\([0-9]\+\)_.*/\1/g'`;
  max=0;
  for v in ${submissions}; do
    if (( $v > $max )); then max=$v; fi;
  done;
  submission="${id}_${max}_proxylab-handin.tar";
  echo -e "${WHITE}Found ${GREEN}${submission}${WHITE} to be the latest submission.";

  echo -e "${WHITE}Making ${BLUE}${dest}${WHITE}.";
  mkdir -p ${dest};

  echo -e "${WHITE}Copying ${GREEN}${submission}${WHITE} into ${BLUE}${dest}${WHITE}.";
  cp ${src}/${submission} ${dest};

  echo -e "${WHITE}Extracting tarball.";
  cd ${dest};
  tar xvf ${submission} &> /dev/null;
}

# Compile and host proxy.
hostProxy() {
  echo "Making proxy.";
  cd ${dest}/proxylab-handout;
  make_out=`make clean; make`;

  if (( $? != 0 )); then 
    echo -e "${WHITE}Make ${RED}failed${WHITE}...";
    echo "${make_out}";
    exit -4;
  fi;

  echo "";
  echo -e "${WHITE}Running ${ORANGE}${id}${WHITE}'s proxy on ${SBLUE}${HOSTNAME}${WHITE}:${MAGENTA}${port}${WHITE}.";

  # Hide color functions and variables from proxy (and any commands afterwards)
  unset ORANGE
  unset SBLUE
  unset MAGENTA
  unset -f BOLD_EXT_COLOR
  unset WHITE
  unset RED
  unset GREEN
  unset BLUE

  # NOTE: As we remove the colors above, this should be the last thing we call.
  ./proxy ${port};
}

main() {
  # Check if someone has already copied over a proxylab-handin.tar
  checkGrading;

  # Check to see if there were any submissions for said user.
  checkHandin;

  # find the most recent submission. (Largest number submission)
  # Make the grading directory if it already doens't exist.
  # Copy over the tarball and extract it.
  setupDirectory;

  # Compile and host proxy.
  hostProxy;
}

################## RUN MAIN ##################
main;
