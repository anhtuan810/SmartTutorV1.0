//
//  Smart Tutor v1.0
//	RecorderAVI
//
//  Created: 2014.08.18
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DirectX.Capture;

namespace RecorderAVI
{
    public class SensorWebcam
    {
        private Filters filters_;
        private Capture capture_;

        public SensorWebcam()
        {
            filters_ = new Filters();
            capture_ = new Capture(filters_.VideoInputDevices[0], filters_.AudioInputDevices[0]);
        }

        public SensorWebcam(int video_id, int audio_id)
        {
            filters_ = new Filters();
            capture_ = new Capture(filters_.VideoInputDevices[video_id], filters_.AudioInputDevices[audio_id]);            
        }

        /// <summary>
        /// Get list of video devices, support the main form
        /// </summary>
        /// <returns></returns>
        public string[] GetVideoDevices()
        {
            string[] devices = new string[filters_.VideoInputDevices.Count];
            for (int i = 0; i < filters_.VideoInputDevices.Count; i++)
            {
                devices[i] = filters_.VideoInputDevices[i].Name;
            }
            return devices;
        }

        /// <summary>
        /// Get list of audio devices, support the main form
        /// </summary>
        /// <returns></returns>
        public string[] GetAudioDevices()
        {
            string[] devices = new string[filters_.AudioInputDevices.Count];
            for (int i = 0; i < filters_.AudioInputDevices.Count; i++)
            {
                devices[i] = filters_.AudioInputDevices[i].Name;
            }
            return devices;
        }


        public void TurnOff()
        {
            capture_.Dispose();
        }

        public bool StartRecordingOrDie(string file_name)
        {
            capture_.VideoCompressor = filters_.VideoCompressors[0];
            capture_.AudioCompressor = filters_.AudioCompressors[0];
            capture_.Filename = file_name;
            capture_.Start();
            return true;
        }

        public void StopRecording()
        {
            capture_.Stop();
        }
    }
}
