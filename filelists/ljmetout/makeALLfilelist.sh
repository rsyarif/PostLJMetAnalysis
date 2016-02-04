


echo "entering BTag_down"
cd BTag_down
#cp ../makeLJMETflist_EOS_3lep.csh .
#sed -i 's|ljmetout/|ljmetout/BTag_down/|' makeLJMETflist_EOS_3lep.csh
#sed -i 's|nominal|BTag_down/|' makeLJMETflist_EOS_3lep.csh
echo "running makeLJMETflist_EOS_3lep.csh"
sc makeLJMETflist_EOS_3lep.csh
echo "exiting BTag_down"
cd ../
echo "entering BTag_up"
cd BTag_up
#cp ../makeLJMETflist_EOS_3lep.csh .
#sed -i 's|ljmetout/|ljmetout/BTag_up/|' makeLJMETflist_EOS_3lep.csh
#sed -i 's|nominal|BTag_up/|' makeLJMETflist_EOS_3lep.csh
echo "running makeLJMETflist_EOS_3lep.csh"
sc makeLJMETflist_EOS_3lep.csh
echo "exiting BTag_up"
cd ../
echo "entering JEC_down"
cd JEC_down
#cp ../makeLJMETflist_EOS_3lep.csh .
#sed -i 's|ljmetout/|ljmetout/JEC_down/|' makeLJMETflist_EOS_3lep.csh
#sed -i 's|nominal|JEC_down/|' makeLJMETflist_EOS_3lep.csh
echo "running makeLJMETflist_EOS_3lep.csh"
sc makeLJMETflist_EOS_3lep.csh
echo "exiting JEC_down"
cd ../
echo "entering JEC_up"
cd JEC_up
#cp ../makeLJMETflist_EOS_3lep.csh .
#sed -i 's|ljmetout/|ljmetout/JEC_up/|' makeLJMETflist_EOS_3lep.csh
#sed -i 's|nominal|JEC_up/|' makeLJMETflist_EOS_3lep.csh
echo "running makeLJMETflist_EOS_3lep.csh"
sc makeLJMETflist_EOS_3lep.csh
echo "exiting JEC_up"
cd ../
echo "entering JER_down"
cd JER_down
#cp ../makeLJMETflist_EOS_3lep.csh .
#sed -i 's|ljmetout/|ljmetout/JER_down/|' makeLJMETflist_EOS_3lep.csh
#sed -i 's|nominal|JER_down/|' makeLJMETflist_EOS_3lep.csh
echo "running makeLJMETflist_EOS_3lep.csh"
sc makeLJMETflist_EOS_3lep.csh
echo "exiting JER_down"
cd ../
echo "entering JER_up"
cd JER_up
#cp ../makeLJMETflist_EOS_3lep.csh .
#sed -i 's|ljmetout/|ljmetout/JER_up/|' makeLJMETflist_EOS_3lep.csh
#sed -i 's|nominal|JER_up/|' makeLJMETflist_EOS_3lep.csh
echo "running makeLJMETflist_EOS_3lep.csh"
sc makeLJMETflist_EOS_3lep.csh
echo "exiting JER_up"
cd ../
echo "entering nominal"
cd nominal
#cp ../makeLJMETflist_EOS_3lep.csh .
#sed -i 's|ljmetout/|ljmetout/nominal/|' makeLJMETflist_EOS_3lep.csh
echo "running makeLJMETflist_EOS_3lep.csh"
sc makeLJMETflist_EOS_3lep.csh
echo "exiting nominal"
cd ../
