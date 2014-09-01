using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace GUI.IO
{    
    class Result
    {
        public double score_overall_;
        public double score_contraction_;
        public double score_direction_;
        public double score_displacement_;
        public double score_energy_;
        public double score_impulse_;
        public double score_stability_;

        public List<bool> binary_balanced_;
        public List<bool> binary_lean_left_;
        public List<bool> binary_lean_right_;

        public List<bool> binary_contraction_low_;
        public List<bool> binary_contraction_average_;
        public List<bool> binary_contraction_high_;

        public List<bool> binary_direction_forward_;
        public List<bool> binary_direction_backward_;

        public List<bool> binary_displacement_moving_;
        public List<bool> binary_displacement_not_moving_;

        public List<bool> binary_energy_low_;
        public List<bool> binary_energy_average_;
        public List<bool> binary_energy_high_;

        public List<bool> binary_impulse_;
    }


    class ResultReader
    {
        public Result ReadData(string result_folder)
        {
            Result result = new Result();
            using (StreamReader reader = new StreamReader(result_folder + "scores.txt"))
            {
                result.score_overall_ = Convert.ToDouble(reader.ReadLine());
                result.score_contraction_ = Convert.ToDouble(reader.ReadLine());
                result.score_direction_ = Convert.ToDouble(reader.ReadLine());
                result.score_displacement_ = Convert.ToDouble(reader.ReadLine());
                result.score_energy_ = Convert.ToDouble(reader.ReadLine());
                result.score_impulse_ = Convert.ToDouble(reader.ReadLine());
                result.score_stability_ = Convert.ToDouble(reader.ReadLine());
            }

            result.binary_balanced_ = ReadOneBinary(result_folder + "binary_balanced.txt");
            result.binary_lean_left_ = ReadOneBinary(result_folder + "binary_lean_left.txt");
            result.binary_lean_right_ = ReadOneBinary(result_folder + "binary_lean_right.txt");

            result.binary_contraction_low_ = ReadOneBinary(result_folder + "binary_contraction_low.txt");
            result.binary_contraction_average_ = ReadOneBinary(result_folder + "binary_contraction_average.txt");
            result.binary_contraction_high_ = ReadOneBinary(result_folder + "binary_contraction_high.txt");

            result.binary_direction_forward_ = ReadOneBinary(result_folder + "binary_direction_forward.txt");
            result.binary_direction_backward_ = ReadOneBinary(result_folder + "binary_direction_backward.txt");

            result.binary_displacement_moving_ = ReadOneBinary(result_folder + "binary_displacement_moving.txt");
            result.binary_displacement_not_moving_ = ReadOneBinary(result_folder + "binary_displacement_not_moving.txt");

            result.binary_energy_low_ = ReadOneBinary(result_folder + "binary_energy_low.txt");
            result.binary_energy_average_ = ReadOneBinary(result_folder + "binary_energy_average.txt");
            result.binary_energy_high_ = ReadOneBinary(result_folder + "binary_energy_high.txt");

            result.binary_impulse_ = ReadOneBinary(result_folder + "binary_impulse.txt");

            return result;
        }


        private List<bool> ReadOneBinary(string file_name)
        {
            List<bool> result = new List<bool>();
            using (StreamReader reader = new StreamReader(file_name))
            {
                while (!reader.EndOfStream)
                {
                    string value = reader.ReadLine();
                    if (value == "0")
                        result.Add(false);
                    else
                        result.Add(true);
                }
            }
            return result;
        }
    }
}
