import ROOT
from ROOT import ertool
from ROOT import geoalgo
from basictool.geoviewer import GeoViewer
import matplotlib.pyplot as plt
import random as rnd
import time
import datetime

plt.ion()

tottime = 0

# track:
viewer = GeoViewer()
viewer._use_box = False
geoAlgo = geoalgo.GeoAlgo()
line1 = geoalgo.LineSegment(0,0,0,0,0,1)
line2 = geoalgo.LineSegment(1,0,0,1,0,1)
pt1 = geoalgo.Vector()
pt2 = geoalgo.Vector()
d = geoAlgo.SqDist(line1,line2,pt1,pt2)
line3 = geoalgo.LineSegment(pt1,pt2)
viewer.add(line1,'ln1','b')
viewer.add(line2,'ln2','r')
viewer.add(line3,'ln3','k')
print 'distance is %.04f'%d
viewer.show()
try:
    counter = input('Hit ENTER when you are ready to close the viewer')
except:
    print "done with this example..."
