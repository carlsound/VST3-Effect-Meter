// https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/interop/example-com-class
// https://blogs.msdn.microsoft.com/murat/2008/11/20/exposing-com-events-c/
//
using System;
using System.Runtime.InteropServices;
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
//
// must be added to the Global Assembly Cache
// using the Visual Studio Command Prompt in Run As Administrator mode
// 1. // cd C:\Program Files\Common Files\VST3
// 2. // gacutil -i Meter_WPF_UI_CS_XAML_AnyCPU.dll
//
// set the build output path to: C:\Program Files\Common Files\VST3
//
namespace Carlsound
{
    namespace Meter
    {
        //**************************************************
        //
        [Guid("931E2D8E-9753-4A36-8C95-6D4E41244FC3")]
        [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
        public interface IMeterControllerViewUserControl
        {
            void show(System.IntPtr hwnd);
            void hide();
            void setInputLevelFeedback(double newInputLevelValue);
            void setColorFeedback(double newColor);
        }
        //
        //**************************************************
        //
        [Guid("DF7603FC-20BB-4E24-9E1C-47F23EF2F47E")]
        [InterfaceType(ComInterfaceType.InterfaceIsIDispatch)]
        public interface IMeterControllerViewUserControlEvents
        {
            void OnThresholdParameterChanged(double newThresholdValue);
        }
        //
        //**************************************************
        //
        /// <summary>
        /// Interaction logic for UserControl1.xaml
        /// </summary>
        /// 
        [ComVisible(true)]
        [Guid("D8B20521-AED1-4546-AC48-B603E8A356B7")]
        [ProgId("Carlsound.Meter.MeterUserControl")]
        [ClassInterface(ClassInterfaceType.None)]
        [ComSourceInterfaces(typeof(IMeterControllerViewUserControlEvents))]
        public partial class MeterUserControl : UserControl, IMeterControllerViewUserControl
        {
            //*****************************************************
            public MeterUserControl()
            {
                InitializeComponent();
                m_inputLevelFeedback = 0;
                m_colorFeedback = 0;
                System.Console.WriteLine("MeterUserControl initialized");
            }

            //*****************************************************
            public void show(IntPtr hwnd)
            {
                m_hwnd = hwnd;
                m_hwndSourceParameters.PositionX = 0;
                m_hwndSourceParameters.PositionY = 0;
                m_hwndSourceParameters.Height = (int) this.Height;
                m_hwndSourceParameters.Width  = (int) this.Width;
                m_hwndSourceParameters.ParentWindow = m_hwnd;
                //m_hwndSourceParameters.WindowStyle = WindowStyle.
                m_hwndSource = new System.Windows.Interop.HwndSource(m_hwndSourceParameters);
                m_hwndSource.RootVisual = this;
            }

            //*****************************************************

            public void hide()
            {
                m_hwndSource.RootVisual = null;
            }

            //*****************************************************
            public void setInputLevelFeedback(double newInputLevelValue)
            {
                m_inputLevelFeedback = newInputLevelValue;
            }

            //*****************************************************
            public void setColorFeedback(double newColor)
            {
                m_colorFeedback = newColor;
            }

            //*****************************************************
            public void onThresholdSliderValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
            {
                if (m_thresholdSlider == sender)
                {
                    OnThresholdParameterChanged(e.NewValue);
                }
            }

            //*****************************************************
            //[ComVisible(false)]
            public delegate void onThresholdParameterChangedDelegate(double newThresholdValue); //No need to expose this delegate
            public event onThresholdParameterChangedDelegate OnThresholdParameterChanged;
            //
            [ComVisible(false)]
            private System.IntPtr m_hwnd;
            private System.Windows.Interop.HwndSource m_hwndSource;
            private System.Windows.Interop.HwndSourceParameters m_hwndSourceParameters;
            //
            private double m_inputLevelFeedback;
            private double m_colorFeedback;
            //private Slider m_thresholdSlider;
        }
    }
}
