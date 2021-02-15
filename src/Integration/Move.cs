using System;
public class Move
    {
        public int x, y, z, u, v, w;

        public Move(int x, int y, int z, int u, int v, int w)
        {
            this.x = x;
            this.y = y;
            this.z = z;
            this.u = u;
            this.v = v;
            this.w = w;
        }


        public Move(string csv)
        {
            string[] e = csv.Split(',');
            if(e.Length != 6)
            {
                Console.WriteLine("CSV file is not formatted correctly");
                return;
            }

            x = Int32.Parse(e[0]);
            y = Int32.Parse(e[1]);
            z = Int32.Parse(e[2]);
            u = Int32.Parse(e[3]);
            v = Int32.Parse(e[4]);
            w = Int32.Parse(e[5]);
        }
    }