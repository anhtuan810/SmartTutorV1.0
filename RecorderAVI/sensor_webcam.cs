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
    public class sensor_webcam
    {
        private Filters filters_;
        private Capture capture_;

        public sensor_webcam()
        {
            filters_ = new Filters();
            capture_ = new Capture(filters_.VideoInputDevices[0], filters_.AudioInputDevices[0]);
        }

        public sensor_webcam(int video_id, int audio_id)
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
            capture_.Filename = file_name;
            capture_.Start();
            return true;
        }

        public void StopRecording()
        {
            capture_.Stop();
        }

        public char[] GrabFrame()
        {
            char[] data = new char[640 * 480 * 3];
            
            return data;
        }
    }
}
