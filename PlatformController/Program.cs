using System;
using PlatformLibrary;

namespace PlatformController {
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

            Console.WriteLine("X Steps: {0:F6}", platform.GetPositionSteps().X);
            Console.WriteLine("Y Steps: {0:F6}", platform.GetPositionSteps().Y);
            Console.WriteLine("Z Steps: {0:F6}", platform.GetPositionSteps().Z);
            Console.WriteLine("U Steps: {0:F6}", platform.GetPositionSteps().U);
            Console.WriteLine("V Steps: {0:F6}", platform.GetPositionSteps().V);
            Console.WriteLine("W Steps: {0:F6}", platform.GetPositionSteps().W);

        }
        static void Main(string[] args) {
            platform.SetFunctionCode(0x1301);
            platform.SetChannelCode(1);
            platform.SetMoveTimeMs(1);

            moveIsSafe = platform.SetPosition(0, 0, 0, 0, 0, 0);
            checkMove(moveIsSafe);

            Console.ReadKey();
        }
    }
}
