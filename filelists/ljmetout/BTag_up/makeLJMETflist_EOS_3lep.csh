
#take in a directory; something like /uscms_data/d2/abarker/Tprime/jobs/101215/ which becomes $1
#it must contain things like DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_25ns/
#which in turn contains root files. 

#example execution
#sc makeLJMETflist.csh /uscms_data/d2/abarker/Tprime/jobs/101215/

#set in=/uscms_data/d2/abarker/Tprime/jobs/101215
set in=/eos/uscms/store/user/lpcljm/LJMet_3lep_122115/BTag_up//
if ($1) then
    set in=$1 # /uscms_data/d2/abarker/Tprime/jobs/101215
endif

# set output_area=/uscms_data/d2/abarker/area2/CMSSW_7_4_7/src/LJMet/Com/filelists/test/
set output_area=/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/BTag_up/
#cd $output_area
set first=1
#foreach d ( `ls -1` )
foreach d ( `els $in` )
	# $in/$d/ looks like '/eos/uscms/store/user/lpcljm/LJMet_2lep_120915/main1/MuonEG_RRD_25ns/'
	els $in/$d/ | grep .root | sed 's|^|'$in/$d'/|' > $output_area/$d.txt

	#if (first == 1) then
	#	set first=0 # skip the first entry, which is $in 
	#else
	#   if (-d $d) then
	#	ls $d/*.root | sed 's|^|'$in'/|' > $output_area/$d.txt
	#   endif # if its a directory
	#endif # end if first entry
end # end for
#cd -
#sleep 20 # makes sure nothing else runs before files appear in output_area
