using System;

namespace Tester {
    class Program {

        static Platform platform = new Platform();

        static bool moveIsSafe = false;

        static void checkMove(bool state) {
            if (state) {
                Console.WriteLine("[+] Move Command Valid, Moving");
                platform.Move();
            } 
            else {
                Console.WriteLine("[!] Move Command Invalid");
            }
        }
        static void Main(string[] args) {
            platform.SetFunctionCode(0x1301);
            platform.SetChannelCode(1);
            platform.SetMoveTimeMs(1);

            moveIsSafe = platform.SetPostion(0, 0, 0, 0, 0, 0);
            checkMove(moveIsSafe);

            Console.ReadLine();
        }
    }
}
