import sys
from ROOT import gSystem
gSystem.Load("libRuiAna_TrackModeling")
from ROOT import sample

try:

    print "PyROOT recognized your class %s" % str(sample)

except NameError:

    print "Failed importing TrackModeling..."

sys.exit(0)

