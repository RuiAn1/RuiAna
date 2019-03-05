import sys

from ROOT import *
#gSystem.Load("libMy_Repo_scratch_area.so")

if len(sys.argv) < 2:
    msg  = '\n'
    msg += "Usage 1: %s $INPUT_ROOT_FILE(s)\n" % sys.argv[0]
    msg += '\n'
    sys.stderr.write(msg)
    sys.exit(1)

from larlite import larlite as fmwk

# prepare viewer for GeoAlgo objects
from ROOT import geoalgo
from basictool.geoviewer import GeoViewer
import matplotlib.pyplot as plt

# load viewer
plt.ion()
viewer = GeoViewer(width=7,height=7)
#viewer = GeoViewer()
viewer._use_box = False
geoAlgo = geoalgo.GeoAlgo()

# Create ana_processor instance
my_proc = fmwk.ana_processor()

# Set input root file
for x in xrange(len(sys.argv)-1):
    my_proc.add_input_file(sys.argv[x+1])

# Specify IO mode
my_proc.set_io_mode(fmwk.storage_manager.kREAD)

# Specify output root file name
#my_proc.set_ana_output_file("PaddleTrackFilter_output.root");

# Attach an analysis unit ... here we use a base class which does nothing.
# Replace with your analysis unit if you wish.
#my_QRA  = fmwk.PaddleTrackFilter()
my_QRA2 = fmwk.PaddleTrackOpflash() 

#my_QRA.SetSaveHistos(True)
#my_proc.add_process(my_QRA)
my_proc.add_process(my_QRA2)

my_QRA2.UseData(False)# Flase use simulation data
#my_QRA2.UseQCluster(True)# True use LightPath
#my_QRA2.UseQCluster(False)# Flase use MCQCluster 
print
print  "Finished configuring ana_processor. Start event loop!"
print
index=0
while my_proc.process_event():
    print index
    index +=1
    print 'new event...'

    retrj  = my_QRA2.Getretrj()
    mctrj  = my_QRA2.Getmctrj()
    w8devi = my_QRA2.Getw8devi()
    devi   = my_QRA2.Getdevi()
    g4sum  = my_QRA2.GetSum_g4()
    plsum  = my_QRA2.GetSum_PL()
    trkid  = 0
    viewer.clear()
        
    if len(retrj)>0 and len(mctrj)>0:
        pt_mc_s = mctrj[0][0]
        pt_re_s = retrj[0][0]
        line_ss = geoalgo.LineSegment(pt_mc_s,pt_re_s)
        viewer.add(line_ss," ","g")
        dist_ss = retrj[0][0].Dist(mctrj[0][0])
        print 'distance between mc and re trk start point is', dist_ss ,'cm !??!'
        print 'weighted deviation for this mc/reco track is ', w8devi,'cm !??!'
        print 'standard deviation for this mc/reco track is ', devi,'cm !??!'
        
    for a in range(0,len(mctrj)):
        pt0 = mctrj[a][0]
        if len(mctrj[a])<5:
            break
        for aa in range(1,5):
            pt1 = mctrj[a][aa]
            pt2 = mctrj[a][aa-1]
            dist = pt0.Dist(pt1)
            if dist>10:
                break
            line = geoalgo.LineSegment(pt1,pt2)
            viewer.add(line," ","r")

    for b in xrange(len(retrj)):
        pt0  = retrj[b][0]
        pt_s = retrj[b][0]
        pt_e = retrj[b][len(retrj[b])-1]
        dist = pt_s.Dist(pt_e)
        if len(retrj[b])<15:
            break
        for bb in range(1,15):
            pt1 = retrj[b][bb]
            pt2 = retrj[b][bb-1]
            dist = pt0.Dist(pt1)
            weight = pt1.Dist(pt2)
            line = geoalgo.LineSegment(pt1,pt2)
            viewer.add(line," ","b")

            pt_h = retrj[b][bb]
            dist = pt_s.Dist(pt_h)
            line0 = geoalgo.LineSegment(retrj[b][bb],retrj[b][bb+1])
            pt3 = geoalgo.Vector()
            pt4 = geoalgo.Vector()
            d = geoAlgo.SqDist(line0,mctrj[0],pt3,pt4)
            pt5 = geoalgo.Vector((pt4[0]-pt3[0])*weight+pt3[0],(pt4[1]-pt3[1])*weight+pt3[1],(pt4[2]-pt3[2])*weight+pt3[2])
            print d
            #line1 = geoalgo.LineSegment(pt3,pt4)
            line1 = geoalgo.LineSegment(pt3,pt5)
            viewer.add(line1,' ','k')
    
    viewer.construct()
    '''
    viewer._ax.set_xlim(-150,300)
    viewer._ax.set_ylim(-120,350)
    viewer._ax.set_zlim(-10,1070)
    viewer._ax._axis3don = False
    '''
    #viewer._fig.canvas.draw()
    #box = geoalgo.AABox(viewer.get_ax_range())
    pt = viewer.get_ax_range()
    pt1x = pt[0][0]
    pt1y = pt[0][1]
    pt1z = pt[0][2]
    pt2x = pt[1][0]
    pt2y = pt[1][1]
    pt2z = pt[1][2]
    distx = pt2x - pt1x
    disty = pt2y - pt1y
    distz = pt2z - pt1z
    if distx>disty and distx>disty:
        box = geoalgo.AABox(pt1x,pt1y,pt1z,pt1x+distx,pt1y+distx,pt1z+distx)
    if disty>distx and disty>distz:
        box = geoalgo.AABox(pt1x,pt1y,pt1z,pt1x+disty,pt1y+disty,pt1z+disty)
    if distz>distx and distz>disty:
        box = geoalgo.AABox(pt1x,pt1y,pt1z,pt1x+distz,pt1y+distz,pt1z+distz)
    viewer.add(box," ","w")
    ratio_pl_g4 = plsum/g4sum 
    print plsum
    print g4sum
    print 'normalization ratio PL/G4 for event is ', ratio_pl_g4,' !??!'
    #viewer._add_label(ratio_pl_g4)
    
    viewer.show()

    
    # go to next event
    usrinput = raw_input("Hit Enter: next evt  ||  q: exit viewer\n")
    if ( usrinput == "q" ):
        sys.exit(0)

# done!
print
print "Finished running ana_processor event loop!"
print

sys.exit(0)
