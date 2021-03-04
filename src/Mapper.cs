namespace SimWatcher
{
    class Mapper{

        public static int[] mapAngles(int pitch, int roll, int yaw){
            int[] returnArr = new int[3];
            int[0] = mapAngle(pitch);
            int[1] = mapAngle(roll);
            int[2] = mapAngle(yaw);
            return returnArr;
        }

        private static int mapAngle(int angle){
            return (30 * (angle + 180)/ 360) - 15;
        }
    }
}