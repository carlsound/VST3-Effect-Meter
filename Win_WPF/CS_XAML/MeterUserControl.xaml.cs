using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

// must be added to the Gloabl Assembly Cache
// using the Visual Studio Command Propt in Run As Administrator mode
// 1. // cd C:\Program Files\Common Files\VST3
// 2. // gacutil -i Meter_WPF_UI_CS_XAML_AnyCPU.dll

// set the build output path to: C:\Program Files\Common Files\VST3

namespace Carlsound
{
    namespace Meter
    {
        /// <summary>
        /// Interaction logic for UserControl1.xaml
        /// </summary>
        public partial class MeterUserControl : UserControl
        {
            public int m_inputLevelFeedback;
            public MeterUserControl()
            {
                InitializeComponent();
            }
        }
    }
}
