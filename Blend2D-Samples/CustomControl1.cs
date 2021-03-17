using System;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;
using Blend2D;

namespace Samples
{
    public partial class CustomControl1 : Control
    {
        #region -- const --

        private const int WM_SIZE = 0x0005;

        private const int WM_PAINT = 0x000F;

        #endregion -- const --

        #region -- fields --

        private BLControlBlt controlBlt;

        private Action<BLImage, BLRectI> drawFunction;

        private int blockNextPaint;

        #endregion -- fields --

        #region -- properties --

        public Action<BLImage, BLRectI> DrawFunction
        {
            get
            {
                return drawFunction;
            }
            set
            {
                drawFunction = value;
                ResetPaintBlock();
                Invalidate();
            }
        }

        public Label Label
        {
            get;
            set;
        }

        #endregion -- properties --

        #region -- constructor --

        public CustomControl1()
        {
            SetStyle(ControlStyles.ResizeRedraw, true);

            controlBlt = new BLControlBlt(ControlPaint);
        }

        #endregion -- constructor --

        #region -- protected methods --

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (controlBlt != null)
                {
                    controlBlt.Dispose();
                    controlBlt = null;
                }
            }

            base.Dispose(disposing);
        }

        protected override void WndProc(ref Message m)
        {
            if (m.Msg == WM_SIZE)
            {
                ResetPaintBlock();
            }
            else if (m.Msg == WM_PAINT)
            {
                if (controlBlt == null || DesignMode)
                {
                    base.WndProc(ref m);
                }
                else
                {
                    controlBlt.Paint(this);
                }
            }
            else
            {
                base.WndProc(ref m);
            }
        }

        #endregion -- protected methods --

        #region -- private methods --

        private void ControlPaint(BLImage image, BLRectI clip)
        {
            if (drawFunction != null && blockNextPaint == 0)
            {
                blockNextPaint++;

                var watch = Stopwatch.StartNew();

                using (var poll = new BLObjectPool())
                {
                    drawFunction(image, clip);
                }

                watch.Stop();

                if (Label != null)
                {
                    Label.Text = $"Elapsed time: {watch.Elapsed.TotalMilliseconds:N2} ms.";
                }

                Console.WriteLine("ControlPaint -> {0}", clip);
            }
            else
            {
                Console.WriteLine("ControlPaint from Buffer -> {0}", clip);
            }
        }

        private void ResetPaintBlock()
        {
            blockNextPaint = 0;
        }

        #endregion -- private methods --
    }
}