//using System;
//using PlatformLibrary;

//namespace PlatformController {
//    class Program {

//        static Platform platform = new Platform();

//        static bool moveIsSafe = false;

//        static void checkMove(bool state) {
//            if (state) {
//                Console.WriteLine("[+] Wrapper Move Command Valid, Moving");
//                platform.Move();
//            }
//            else {
//                Console.WriteLine("[!] Wrapper Move Command Invalid");
//            }

//            Console.WriteLine("X Steps: {0:F6}", platform.GetPositionSteps().X);
//            Console.WriteLine("Y Steps: {0:F6}", platform.GetPositionSteps().Y);
//            Console.WriteLine("Z Steps: {0:F6}", platform.GetPositionSteps().Z);
//            Console.WriteLine("U Steps: {0:F6}", platform.GetPositionSteps().U);
//            Console.WriteLine("V Steps: {0:F6}", platform.GetPositionSteps().V);
//            Console.WriteLine("W Steps: {0:F6}", platform.GetPositionSteps().W);

//        }
//        static void Main(string[] args) {
//            platform.SetFunctionCode(0x1301);
//            platform.SetChannelCode(1);
//            platform.SetMoveTimeMs(1);

//            for (double i = 0; i < 360 * 4; i += 10.0) {
//                double x = Math.Sin(i * 3.14159 / 180.0) * 20.0;
//                double y = Math.Cos(i * 3.14159 / 180.0) * 20.0;
//                double yaw = 0;// Math.Cos(i * 3.14159 / 180.0 * 2) * 20.0;
//                moveIsSafe = platform.SetPosition(0, 0, 230, (int)yaw, (int)x, (int)y);
//                checkMove(moveIsSafe);
//                System.Threading.Thread.Sleep(100);
//            }
              
//            checkMove(moveIsSafe);

//            Console.ReadKey();
//        }
//    }
//}
