using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


class PlatformPosition
{
    public int x;
    public int y;
    public int z;
    public int u;
    public int v;
    public int w;

    public PlatformPosition(int x, int y, int z, int u, int v, int w)
    {
        this.x = x;
        this.y = y;
        this.z = z;
        this.u = u;
        this.v = v;
        this.w = w;
    }
    
    public static PlatformPosition neutralPosition()
    {
        return new PlatformPosition(0,0,20,0,0,0);
    }
}
