import sys
from ROOT import gSystem
gSystem.Load("libRuiAna_HelloCryo")
from ROOT import sample

try:

    print "PyROOT recognized your class %s" % str(sample)

except NameError:

    print "Failed importing HelloCryo..."

sys.exit(0)

