using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace GUI.RequiredInterface
{
    class GUIFeatureInterface
    {
        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool IGenerateFeaturesFromONI(string oni_file, string data_folder);

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void IPerformFeatureAnalysis(string data_folder);

        [DllImport(@"InterfaceForGUI.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr IGetFeatureScores();



        public bool GenerateFeaturesFromONI(string oni_file, string data_folder)
        {
            return IGenerateFeaturesFromONI(oni_file, data_folder);
        }

        public void PerformFeatureAnalysis(string data_folder)
        {
            IPerformFeatureAnalysis(data_folder);
        }

        public double[] GetScores()
        {
            IntPtr scores = IGetFeatureScores();
            double[] result = new double[7];
            Marshal.Copy(scores, result, 0, 7);
            return result;
        }
    }
}
