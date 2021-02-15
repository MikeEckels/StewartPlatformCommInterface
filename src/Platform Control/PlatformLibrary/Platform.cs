using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace PlatformLibrary {
    public class Platform
    {
        [DllImport("StewartPlatformCommInterface.dll")]
        private static extern IntPtr CreatePlatform();

        [DllImport("StewartPlatformCommInterface.dll")]
        private static extern void DeletePlatform(IntPtr platformPointer);

        [DllImport("StewartPlatformCommInterface.dll")]
        private static extern void ResetW(IntPtr platformPointer);

        [DllImport("StewartPlatformCommInterface.dll")]
        private static extern void StopW(IntPtr platformPointer);

        [DllImport("StewartPlatformCommInterface.dll")]
        private static extern void SetFunctionCodeW(IntPtr platformPointer, int code);

        [DllImport("StewartPlatformCommInterface.dll")]
        private static extern void SetChannelCodeW(IntPtr platformPointer, int code);

        [DllImport("StewartPlatformCommInterface.dll")]
        private static extern void SetMoveTimeMsW(IntPtr platformPointer, int milliseconds);

        [DllImport("StewartPlatformCommInterface.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        private static extern bool SetPositionW(IntPtr platformPointer, int x, int y, int z, int u, int v, int w);

        [DllImport("StewartPlatformCommInterface.dll")]
        private static extern void SetRegisterW(IntPtr platformPointer, ushort channelCode, ushort registerAddress, ushort value);

        [DllImport("StewartPlatformCommInterface.dll")]
        private static extern ActuatorLengths GetPositionStepsW(IntPtr platformPointer);

        [DllImport("StewartPlatformCommInterface.dll")]
        private static extern void MoveW(IntPtr platformPointer);

        private readonly IntPtr _platformPointer;

        public Platform()
        {
            _platformPointer = CreatePlatform();
        }

        ~Platform()
        {
            DeletePlatform(_platformPointer);
        }

        public void Reset()
        {
            ResetW(_platformPointer);
        }

        public void Stop()
        {
            StopW(_platformPointer);
        }

        public void SetFunctionCode(int code)
        {
            SetFunctionCodeW(_platformPointer, code);
        }

        public void SetChannelCode(int code)
        {
            SetChannelCodeW(_platformPointer, code);
        }

        public void SetMoveTimeMs(int milliseconds)
        {
            SetMoveTimeMsW(_platformPointer, milliseconds);
        }

        public bool SetPostion(int x, int y, int z, int u, int v, int w)
        {
            return SetPositionW(_platformPointer, x, y, z, u, v, w);
        }

        public void SetRegister(ushort channelCode, ushort registerAddress, ushort value)
        {
            SetRegisterW(_platformPointer, channelCode, registerAddress, value);
        }

        public ActuatorLengths GetPositionSteps()
        {
            return GetPositionStepsW(_platformPointer);
        }

        public void Move()
        {
            MoveW(_platformPointer);
        }
    }
}
