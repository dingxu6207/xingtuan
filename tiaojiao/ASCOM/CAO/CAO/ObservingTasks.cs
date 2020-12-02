using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CAO
{
    class ObservingTasks
    {
        struct ImagePara
        {
            byte ImageType;//Light,Dark,Bias,Flat
            string FilterWheel;
            double ExposureDuration;
            UInt16 ImageNum;//How many Images to expose
        }
        struct ObservintTargets
        {
            double TargetRightAscension;
            double TargetDeclination;
            ImagePara[] Image;  
        }
    }
}
