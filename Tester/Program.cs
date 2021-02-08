using System;

namespace Tester {
    class Program {

        static Platform platform = new Platform();

        static bool moveIsSafe = false;

        static void checkMove(bool state) {
            if (state) {
                Console.WriteLine("[+] Wrapper Move Command Valid, Moving");
                platform.Move();
            } 
            else {
                Console.WriteLine("[!] Wrapper Move Command Invalid");
            }

            Console.WriteLine("X Steps: " + platform.GetXsteps());
            Console.WriteLine("Y Steps: " + platform.GetYsteps());
            Console.WriteLine("Z Steps: " + platform.GetZsteps());
            Console.WriteLine("U Steps: " + platform.GetUsteps());
            Console.WriteLine("V Steps: " + platform.GetVsteps());
            Console.WriteLine("W Steps: " + platform.GetWsteps());
        }
        static void Main(string[] args) {
            platform.SetFunctionCode(0x1301);
            platform.SetChannelCode(1);
            platform.SetMoveTimeMs(1);

            moveIsSafe = platform.SetPostion(0, 0, 0, 0, 0, 0);
            checkMove(moveIsSafe);

            Console.ReadKey();
        }
    }
}
