extern "C" { __declspec(dllexport) void TurnOnKinectSensor(); }
extern "C" { __declspec(dllexport) void StartRecordingONI(char* file_name); }
extern "C" { __declspec(dllexport) void StopRecordingONI(); }
extern "C" { __declspec(dllexport) void TurnOffKinectSensor(); }
extern "C" { __declspec(dllexport) char* GrabFrame(); }