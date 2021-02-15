namespace SimWatcher
{
    class SimulateState : State{
        private Platform p; // should there be multiple implementations in this class (I think yes)
        private SysQuerierImp sq;
        private int queryFreq = 10;


        public SimulateState(){
            sq = new SysQuerierImp(Resources.simulateVars);  //vars to watch = "Plane Pitch Degrees" , "Plane Bank Degrees", "Plane Heading Degrees True"
            sq.setRequestFreq(queryFreq);
            sq.DataDispatch += handleSimResponse;
            sq.connectToSim();
            p = new Platform(); // this will likely look more like: p = new SimplePlatformControl or p = new AdvancedPlatformControl
        }
        
        private void handleSimResponse(object sender, EventArgs e)
        {
            var data = (DequeueEventArgs)e;
            Hashtable t = data.t;
            int[] mappedAngles = Mapper.mapAngles(t["Plane Pitch Degrees"], t["Plane Bank Degrees"], t["Plane Heading Degrees True"]);
            p.setAnglePositions(mappedAngles[0], mappedAngles[1], mappedAngles[2]);
            p.move();
        }
        
    }
}