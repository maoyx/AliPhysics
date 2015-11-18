export BASEDIR=/cvmfs/alice.cern.ch/x86_64-2.6-gnu-4.1.2/Packages
export ALIEN_DIR=$BASEDIR/AliEn-Runtime/v2-19-xrd2-4
export ROOTSYS=$BASEDIR/ROOT/v5-34-30-alice-7
export ALICE_ROOT=$BASEDIR/AliRoot/v5-07-10-1
export ALICE_PHYSICS=$BASEDIR/AliPhysics/v5-07-10-01-1
export GEANT3=$BASEDIR/Packages/GEANT3/v2-0-1
export LD_LIBRARY_PATH=
export LD_LIBRARY_PATH=$ALIEN_DIR/api/lib:$ALIEN_DIR/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$ROOTSYS/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$GEANT3/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$ALICE_ROOT/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$ALICE_PHYSICS/lib:$LD_LIBRARY_PATH
export PATH=/usr/sue/bin:/usr/lib64/qt-3.3/bin:/usr/kerberos/sbin:/usr/kerberos/bin:/usr/local/bin:/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/sbin
export PATH=$ALIEN_DIR/api/bin:$ALIEN_DIR/bin:$PATH
export PATH=$ROOTSYS/bin:$PATH
export PATH=$ALICE_ROOT/bin:$PATH
export PATH=$ALICE_PHYSICS/bin:$PATH
export GSHELL_ROOT=$ALIEN_DIR/api
export GSHELL_NO_GCC=1


