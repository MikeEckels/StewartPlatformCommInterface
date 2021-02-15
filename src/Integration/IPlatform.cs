interface IPlatform{
    bool connect();
    bool getIsConnected();
    bool setPosition(int x, int y, int z, int u, int v, int w);
    void move();
    Move getPosition();//this is traaaaaash
}