using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace FlightSimTests
{
   [TestClass]
   public class SimulationControlTests
   {
       [TestMethod]
       public void CanConnectToPlatform()
       {
           //setup
           Platform p = new SimulatedPlatform();
           //act
           p.connect();
           //test
           Assert.isTrue(p.isConnected, "Platform Not Connected");
       }

       [TestMethod]
       public void CanMovePlatform()
       {
           //setup
           Platform p = new SimulatedPlatform();
           const int x = 10; const int y = -10; const int z = 5;
           const int u = 0; const int v = 0; const int w = 0;
           PlatformPosition platPos = new PlatformPosition(x,y,x,u,v,w);
           p.connect();
           //move platform
           p.SetPosition(platPos);
           p.move()
           //did platform move to desired location
           PlatformPosition confirmPos = p.getPosition();
           dsss
       }
   }
}