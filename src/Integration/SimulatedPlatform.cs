using System;

class SimulatedPlatform : IPlatform{
    private bool isConnected = false;
    private Move currentMove;

    public bool connect(){
        isConnected = true;
        return isConnected;
    }

    public bool getIsConnected() { return isConnected; }

    public bool setPosition(int x, int y, int z, int u, int v, int w)
    {
        currentMove = new Move(x, y, z, u, v, w);
        return true;
    }

    public void move()
    {
        Console.WriteLine("Woohoo Simulated Platform Moved");
    }

    public Move getPosition()
    {
        return this.currentMove;
    }
}