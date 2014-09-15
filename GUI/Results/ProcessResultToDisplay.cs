//
//  Smart Tutor v1.0
//	GUI
//  Perform extra processing on the retrieved result, before displaying on GUI
//  Just simply for decoration, or make it simpler for user to understand
//
//  Created: 2014.09.15
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GUI.IO;

namespace GUI.Results
{
    class ProcessResultToDisplay
    {
        Result result_;

        public ProcessResultToDisplay(Result result)
        {
            result_ = result;
        }


        /// <summary>
        /// Smooth the binary appearance of codewords
        /// </summary>
        /// <returns></returns>
        public Result SmoothBinaryCodeword()
        {
            Result result = result_;
            const double kRatio = 0.8;

            return result;
        }
    }
}
